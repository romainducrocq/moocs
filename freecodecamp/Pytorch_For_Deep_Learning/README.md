# PyTorch for Deep Learning 
## Aakash N S, freeCodeCamp
Inspired by [PyTorch Tutorial for Deep Learning Researchers](https://github.com/yunjey/pytorch-tutorial), by Yunjey Choi 
****

### Syllabus

- Part 1: PyTorch Basics: Tensors & Gradients  
- Part 2: Gradient Descent and Linear Regression with PyTorch  
- Part 3: Working with Images & Logistic Regression in PyTorch  
- Part 4: Training Deep Neural Networks on a GPU with PyTorch  
- Part 5: Image Classification using Convolutional Neural Networks in PyTorch  

****

### Google colab:
- https://colab.research.google.com/notebooks/intro.ipynb
Upload: File > Upload Notebook > Github  
Download: File > Download > Download .ipynb, Files > Content > Download  
Delete: Runtime > Factory Reset Runtime, File > Open Notebook > Recent > Clear History  

### Conda venv: 
- https://uoa-eresearch.github.io/eresearch-cookbook/recipe/2014/11/20/conda/  

. ~/.bashrc -conda  
<br>
(base) conda create -n Pytorch_For_Deep_Learning python=3.6 anaconda  
(base) conda activate Pytorch_For_Deep_Learning  
(Pytorch_For_Deep_Learning) conda install -n Pytorch_For_Deep_Learning pip  
(Pytorch_For_Deep_Learning) pip install numpy torch==1.7.0+cpu torchvision==0.8.1+cpu torchaudio==0.7.0 -f https://download.pytorch.org/whl/torch_stable.html  
(Pytorch_For_Deep_Learning) jupyter-notebook --allow-root &  
(Pytorch_For_Deep_Learning) conda deactivate  
(base) conda remove -n Pytorch_For_Deep_Learning --all  
<br>
. ~/.bashrc  

****

~/.bashrc:
```bash
if [ "$1" = "-conda" ]; then
	# >>> conda initialize >>>
	# !! Contents within this block are managed by 'conda init' !!
	__conda_setup="$('/opt/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
	if [ $? -eq 0 ]; then
	    eval "$__conda_setup"
	else
	    if [ -f "/opt/anaconda3/etc/profile.d/conda.sh" ]; then
		. "/opt/anaconda3/etc/profile.d/conda.sh"
	    else
		export PATH="/opt/anaconda3/bin:$PATH"
	    fi
	fi
	unset __conda_setup
	# <<< conda initialize <<<
fi
```

