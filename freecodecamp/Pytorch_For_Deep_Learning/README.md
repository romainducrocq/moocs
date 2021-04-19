# PyTorch for Deep Learning 
## Aakash N S, freeCodeCamp
****

### Syllabus

- 1. PyTorch Basics: Tensors & Gradients  


****

### Conda venv: 
- Conda venv: https://uoa-eresearch.github.io/eresearch-cookbook/recipe/2014/11/20/conda/  

. ~/.bashrc -conda  
<br>
(base) conda create -n Pytorch_For_Deep_Learning python=3.6 anaconda  
(base) conda activate Pytorch_For_Deep_Learning  
(Pytorch_For_Deep_Learning) conda install -n Pytorch_For_Deep_Learning pip  
(Pytorch_For_Deep_Learning) pip install numpy torch==1.7.0+cpu torchvision==0.8.1+cpu torchaudio==0.7.0 -f https://download.pytorch.org/whl/torch_stable.html  
(Pytorch_For_Deep_Learning) jupyter-notebook --allow-root  
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

