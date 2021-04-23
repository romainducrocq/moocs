"""
Train:
python3 main.py -n_games 250 -algo DuelingDDQNAgent

Test:
python3 main.py -n_games 10 -algo DuelingDDQNAgent -eps 0 -eps_min 0 -load_checkpoint True

Observe:
python3 main.py -n_games 10 -algo DuelingDDQNAgent -eps 0 -eps_min 0 -load_checkpoint True -render True
"""

import os
import argparse
import gym
from gym import wrappers
import numpy as np
import agents as Agents
from utils import plot_learning_curve, make_env
import time


if __name__ == '__main__':
    start_time = time.time()

    parser = argparse.ArgumentParser(description="Deep Q-learning: From Paper to Code")
    # the hyphen makes the argument optional
    parser.add_argument('-n_games', type=int, default=1, help='Number of games to play')
    parser.add_argument('-lr', type=float, default=0.0001, help='Learning rate for optimizer')
    parser.add_argument('-gamma', type=float, default=0.99, help='Discount factor for update equation')
    parser.add_argument('-eps_min', type=float, default=0.1, help='Minimum value for epsilon in epsilon greedy action selection')
    parser.add_argument('-eps_dec', type=float, default=1e-5, help='Linear factor for decreasing epsilon')
    parser.add_argument('-eps', type=float, default=1.0, help='Starting value for epsilon in epsilon-greedy action selection')
    parser.add_argument('-max_mem', type=int, default=50000, help='Maximum size for memory replay buffer')  # ~13GB
    parser.add_argument('-repeat', type=int, default=4, help='Number of frames to repeat & stack for environment')
    parser.add_argument('-bs', type=int, default=32, help='Batch size for replay memory sampling')
    parser.add_argument('-update_target', type=int, default=10000, help='Interval for updating target network')
    parser.add_argument('-env', type=str, default='PongNoFrameskip-v4', help='Atari environment:\n' +
                                                                             '- PongNoFrameSkip-v4\n' +
                                                                             '- BreakoutNoFrameSkip-v4\n' +
                                                                             '- SpaceInvadersNoFrameskip-v4\n' +
                                                                             '- EnduroNoFrameskip-v4\n' +
                                                                             '- AtlantisNoFrameskip-v4\n')
    parser.add_argument('-gpu', type=str, default='0', help='GPU: 0 or 1')
    parser.add_argument('-load_checkpoint', type=bool, default=False, help='Load model checkpoint')
    parser.add_argument('-render', type=bool, default=False, help='Render video')
    parser.add_argument('-path_models', type=str, default='models/', help='Path for model saving/loading')
    parser.add_argument('-path_plots', type=str, default='plots/', help='Path for plots')
    parser.add_argument('-path_videos', type=str, default='videos/', help='Path for videos')
    parser.add_argument('-algo', type=str, default='DQNAgent', help='DQNAgent/DDQNAgent/DuelingDQNAgent/DuelingDDQNAgent')
    parser.add_argument('-clip_rewards', type=bool, default=False, help='Clip rewards to range -1 to 1')
    parser.add_argument('-no_ops', type=int, default=0, help='Max number of no ops for testing')
    parser.add_argument('-fire_first', type=bool, default=False, help='Set first action of episode to fire')
    args = parser.parse_args()

    os.environ['CUDA_DEVICE_ORDER'] = 'PCI_BUS_ID'
    os.environ['CUDA_VISIBLE_DEVICES'] = args.gpu

    env = make_env(args.env, repeat=args.repeat, clip_rewards=args.clip_rewards, no_ops=args.no_ops, fire_first=args.fire_first)

    best_score = -np.inf

    agent = getattr(Agents, args.algo)(
        gamma=args.gamma,
        epsilon=args.eps,
        lr=args.lr,
        input_dims=env.observation_space.shape,
        n_actions=env.action_space.n,
        mem_size=args.max_mem,
        eps_min=args.eps_min,
        batch_size=args.bs,
        update_target_freq=args.update_target,
        eps_dec=args.eps_dec,
        chkpt_dir=args.path_models,
        algo=args.algo,
        env_name=args.env
    )

    if args.load_checkpoint:
        agent.load_models()

        if args.render:
            env = wrappers.Monitor(env, args.path_videos, video_callable=lambda episode_id: True, force=True)

    file_name = args.algo + '_' + args.env + '_lr_' + str(args.lr) + '_' + str(args.n_games) + '_games'
    figure_file = 'plots/' + file_name + '.png'

    n_steps, scores, eps_history, steps_array = 0, [], [], []

    for i in range(args.n_games):
        done = False
        score = 0
        observation = env.reset()

        while not done:
            action = agent.choose_action(observation)
            new_observation, reward, done, info = env.step(action)
            score += reward

            if args.load_checkpoint and args.render:
                env.render()

            if not args.load_checkpoint:
                agent.store_transition(observation, action, reward, new_observation, int(done))
                agent.learn()

            observation = new_observation
            n_steps += 1

        scores.append(score)
        steps_array.append(n_steps)

        avg_score = np.mean(scores[-100:])
        print()
        print('Episode: ', i+1)
        print('Score:', score)
        print('Average score: %.1f' % avg_score)
        print('Best score: %.1f' % best_score)
        print('Epsilon: %.2f' % agent.epsilon)
        print('Steps:', n_steps)
        print("--- %s seconds ---" % round((time.time() - start_time), 2))

        if avg_score > best_score:
            if not args.load_checkpoint:
                agent.save_models()
            best_score = avg_score

        eps_history.append(agent.epsilon)

    plot_learning_curve(steps_array, scores, eps_history, figure_file)

