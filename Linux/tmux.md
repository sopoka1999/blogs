## tmux
Ctrl+b %  划分左右两个窗格。
Ctrl+b "  划分上下两个窗格。
Ctrl+b <arrow key>  
光标切换到其他窗格。<arrow key>是指向要切换到的窗格的方向键，比如切换到下方窗格，就按方向键↓。
Ctrl+b :
setw synchronize-panes on
Ctrl+b :
setw synchronize-panes off

关闭所有会话
tmux kill-server