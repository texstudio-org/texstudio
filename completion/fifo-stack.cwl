# fifo-stack package
# 1/18/2022 for v1.0
# copied from http://mirrors.ctan.org/macros/latex/contrib/fifo-stack/fifo-stack.cwl

#include:ifthen

\FSCreate{fifoStackName}{defaultValue}
\FSClear{fifoStackName}
\FSDestroy{fifoStackName}
\FSPush{fifoStackName}{value}
\FSPop{fifoStackName}
\FSTop{fifoStackName}
\FSShowTop{fifoStackName}
\FSUnshift{fifoStackName}{value}
\FSShift{fifoStackName}
\FSBottom{fifoStackName}
\FSShowBottom{fifoStackName}
\FSSize{fifoStackName}