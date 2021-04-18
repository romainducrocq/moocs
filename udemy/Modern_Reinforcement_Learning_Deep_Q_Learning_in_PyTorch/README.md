# Modern Reinforcement Learning: Deep Q Learning in PyTorch
## Phil Tabor, Udemy

****

### Syllabus

**Section 1: Introduction**
- 1. What You Will Learn In This Course  
- 2. Required Background, software, and hardware  
- 3. How to Succeed in this Course  

**Section 2: Fundamentals of Reinforcement Learning**
- 4. Agents, Environments, and Actions  
- 5. Markov Decision Processes  
- 6. Value Functions, Action Value Functions, and the Bellman Equation  
- 7. Model Free vs. Model Based Learning  
- 8. The Explore-Exploit Dilemma  
- 9. Temporal Difference Learning  

**Section 3: Deep Learning Crash Course**
- 10. Dealing with Continuous State Spaces with Deep Neural Networks  
- 11. Naive Deep Q Learning in Code: Step 1 - Coding the Deep Q Network  
- 13. Naive Deep Q Learning in Code: Step 3 - Coding the Main Loop and Learning  
- 14. Naive Deep Q Learning in Code: Step 4 - Verifying the Functionality of Our Code  
- 15. Naive Deep Q Learning in Code: Step 5 - Analyzing Our Agent's Performance  
- 16. Dealing with Screen Images with Convolutional Neural Networks  

**Section 4: Human Level Control Through Deep Reinforcement Learning, From Paper to Code**
- 17. How to Read Deep Learning Papers
- 18. Analyzing the Paper
- 19. How to Modify the OpenAI Gym Atari Environments
- 20. How to Preprocess the OpenAI Gym Atari Screen Images
- 21. How to Stack the Preprocessed Atari Screen Images
- 22. How to Combine All the Changes
- 23. How to Add Reward Clipping, Fire First, and No Ops
- 24. How to Code the Agent's Memory
- 25. How to Code the Deep Q Network
- 26. Coding the Deep Q Agent: Step 1 - Coding the Constructor
- 27. Coding the Deep Q Agent: Step 2 - Epsilon-Greedy Action Selection
- 28. Coding the Deep Q Agent: Step 3 - Memory, Model Saving and Network Copying
- 29. Coding the Deep Q Agent: Step 4 - The Agent's Learn Function
- 30. Coding the Deep Q Agent: Step 5 - The Main Loop and Analyzing the Performance

****

### Software Requirements

- Python 3.6
> wget https://www.python.org/ftp/python/3.6.13/Python-3.6.13.tar.xz  
> tar -xvf Python-3.6.13.tar.xz && rm -v Python-3.6.13.tar.xz && cd Python-3.6.13  
> apt-get install build-essential sqlite3 libsqlite3-dev libbz2-dev zlib1g-dev  
> ./configure && make && make altinstall  

- venv
> mkdir venv && python3.6 -m venv venv/  
> source venv/bin/activate  
> deactivate  

- torch, torchvision, numpy, matplotlib, gym, box2d-py, atari-py, opencv-python  
> (venv) pip3 install torch torchvision numpy matplotlib gym box2d-py atari-py opencv-python  


