import numpy as np
from ddqn_agent import DDQNAgent
from utils import make_env, plot_learning_curve
import time


if __name__ == "__main__":
    start_time = time.time()

    env = make_env('PongNoFrameskip-v4')
    best_score = -np.inf
    load_checkpoint = False
    n_games = 250
    agent = DDQNAgent(
        gamma=0.99,
        epsilon=1.0,
        lr=0.0001,
        input_dims=env.observation_space.shape,
        n_actions=env.action_space.n,
        mem_size=50000,
        eps_min=0.1,
        batch_size=32,
        update_target_freq=1000,
        eps_dec=1e-5,
        chkpt_dir='models/',
        algo='DDQN',
        env_name='PongNoFrameskip-v4'
    )

    if load_checkpoint:
        agent.load_models()

    file_name = agent.algo + '_' + agent.env_name + '_lr_' + str(agent.lr) + '_' + str(n_games) + '_games'
    figure_file = 'plots/' + file_name + '.png'

    n_steps, scores, eps_history, steps_array = 0, [], [], []

    for i in range(n_games):
        done = False
        score = 0
        observation = env.reset()

        while not done:
            action = agent.choose_action(observation)
            new_observation, reward, done, info = env.step(action)
            score += reward

            if not load_checkpoint:
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
            if not load_checkpoint:
                agent.save_models()
            best_score = avg_score

        eps_history.append(agent.epsilon)

    plot_learning_curve(steps_array, scores, eps_history, figure_file)
