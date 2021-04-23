import numpy as np
import torch as T
from dueling_deep_q_network import DuelingDeepQNetwork
from replay_memory import ReplayBuffer


class DuelingDDQNAgent:
    def __init__(self, gamma, epsilon, lr, n_actions, input_dims, mem_size, batch_size, eps_min=0.01, eps_dec=5e-7,
                 update_target_freq=1000, algo=None, env_name=None, chkpt_dir='tmp/dueling_ddqn'):
        self.gamma = gamma
        self.epsilon = epsilon
        self.lr = lr
        self.n_actions = n_actions
        self.input_dims = input_dims
        self.batch_size = batch_size
        self.eps_min = eps_min
        self.eps_dec = eps_dec
        self.update_target_freq = update_target_freq
        self.algo = algo
        self.env_name = env_name
        self.chkpt_dir = chkpt_dir
        self.action_space = [i for i in range(self.n_actions)]
        self.learn_step_counter = 0

        self.memory = ReplayBuffer(mem_size, input_dims, n_actions)

        self.q_online = DuelingDeepQNetwork(self.lr, self.n_actions, input_dims=self.input_dims,
                                            name=self.env_name+'_'+self.algo+''+'_q_online', chkpt_dir=self.chkpt_dir)

        self.q_target = DuelingDeepQNetwork(self.lr, self.n_actions, input_dims=self.input_dims,
                                            name=self.env_name+'_'+self.algo+'_q_target', chkpt_dir=self.chkpt_dir)

    def choose_action(self, observation):
        if np.random.random() > self.epsilon:
            state_t = T.tensor([observation], dtype=T.float).to(self.q_online.device)
            _, advantages_t = self.q_online.forward(state_t)
            action = T.argmax(advantages_t).item()
        else:
            action = np.random.choice(self.action_space)

        return action

    def store_transition(self, state, action, reward, new_state, done):
        self.memory.store_transition(state, action, reward, new_state, done)

    def sample_memory(self):
        states, actions, rewards, new_states, dones = self.memory.sample_buffer(self.batch_size)

        states_t = T.tensor(states).to(self.q_online.device)
        actions_t = T.tensor(actions).to(self.q_online.device)
        rewards_t = T.tensor(rewards).to(self.q_online.device)
        new_states_t = T.tensor(new_states).to(self.q_online.device)
        dones_t = T.tensor(dones).to(self.q_online.device)

        return states_t, actions_t, rewards_t, new_states_t, dones_t

    def update_target_network(self):
        if self.learn_step_counter % self.update_target_freq == 0:
            self.q_target.load_state_dict(self.q_online.state_dict())

    def decrement_epsilon(self):
        self.epsilon = self.epsilon - self.eps_dec if self.epsilon > self.eps_min else self.eps_min

    def save_models(self):
        self.q_online.save_checkpoint()
        self.q_target.save_checkpoint()

    def load_models(self):
        self.q_online.load_checkpoint()
        self.q_target.load_checkpoint()

    def learn(self):
        if self.memory.mem_cntr < self.batch_size:
            return

        self.q_online.optimizer.zero_grad()

        self.update_target_network()

        states_t, actions_t, rewards_t, new_states_t, dones_t = self.sample_memory()

        indices = np.arange(self.batch_size)

        V_online, A_online = self.q_online.forward(states_t)
        V_targets_target, A_targets_target = self.q_target.forward(new_states_t)
        V_targets_online, A_targets_online = self.q_online.forward(new_states_t)

        q_pred = T.add(V_online, (A_online - A_online.mean(dim=1, keepdim=True)))[indices, actions_t]
        q_targets_target = T.add(V_targets_target, (A_targets_target - A_targets_target.mean(dim=1, keepdim=True)))
        q_targets_online = T.add(V_targets_online, (A_targets_online - A_targets_online.mean(dim=1, keepdim=True)))

        max_actions = T.argmax(q_targets_online, dim=1)

        q_targets_target[dones_t] = 0.0

        q_target = rewards_t + self.gamma*q_targets_target[indices, max_actions]

        loss = self.q_online.loss(q_target, q_pred).to(self.q_online.device)
        loss.backward()
        self.q_online.optimizer.step()
        self.learn_step_counter += 1

        self.decrement_epsilon()
