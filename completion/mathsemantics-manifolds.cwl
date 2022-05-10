# mathsemantics-manifolds package
# Matthew Bertucci 2022/05/08 for v1.0.0

#include:mathsemantics-semantic

\bitangentSpaceSymbol#*m
\cotangentSpaceSymbol#*m
\covariantDerivativeSymbol#*
\secondCovariantDerivativeSymbol#*m
\geodesicSymbol#*m
\wideparen{arg}#m
\geodesicArcSymbol{arg}#*m
\parallelTransportSymbol#*
\retractionSymbol#*
\tangentSpaceSymbol#*m
\tensorSpaceSymbol#*m
\vectorTransportSymbol#*
\bitangentSpace{point}#m
\bitangentSpace{point}[manifold]#m
\cotangentSpace{point}#m
\cotangentSpace{point}[manifold]#m
\cotangentBundle#m
\cotangentBundle[manifold]#m
\covariantDerivative{vector field}#m
\covariantDerivative{vector field}[tensor field]#m
\expOp#*m
\exponential{base}#m
\exponential{base}(arg)#m
\exponential[scale%keyvals]{base}#m
\exponential[scale%keyvals]{base}(arg)#m
\geodesic<s>%|#m
\geodesic<s>(%<eval point%>)#m
\geodesic<s>[%<scale%>]#m
\geodesic<s>[%<scale%>](%<eval point%>)#m
\geodesic<style>{t0}{t1}#m
\geodesic<style>{t0}{t1}(eval point)#m
\geodesic<style>[scale]{t0}{t1}#m
\geodesic<style>[scale]{t0}{t1}(eval point)#m
\geodesic{t0}{t1}#m
\geodesic{t0}{t1}(eval point)#m
\geodesic[scale]{t0}{t1}#m
\geodesic[scale]{t0}{t1}(eval point)#m
\geodesic|%<symbol%>|<%<style%>>{%<t0%>}{%<t1%>}#*m
\geodesic|%<symbol%>|<%<style%>>{%<t0%>}{%<t1%>}(%<eval point%>)#*m
\geodesic|%<symbol%>|<%<style%>>[%<scale%>]{%<t0%>}{%<t1%>}#*m
\geodesic|%<symbol%>|<%<style%>>[%<scale%>]{%<t0%>}{%<t1%>}(%<eval point%>)#*m
\geodesic|%<symbol%>|{%<t0%>}{%<t1%>}#*m
\geodesic|%<symbol%>|{%<t0%>}{%<t1%>}(%<eval point%>)#m
\geodesic|%<symbol%>|[%<scale%>]{%<t0%>}{%<t1%>}#*m
\geodesic|%<symbol%>|[%<scale%>]{%<t0%>}{%<t1%>}(%<eval point%>)#m
\logOp#*m
\logarithm{base}#m
\logarithm{base}(arg)#m
\logarithm[scale%keyvals]{base}#m
\logarithm[scale%keyvals]{base}(arg)#m
\inverseRetract{base}#m
\inverseRetract{base}(arg)#m
\inverseRetract[scale%keyvals]{base}#m
\inverseRetract[scale%keyvals]{base}(arg)#m
\lie{arg1}{arg2}#m
\lie[scale%keyvals]{arg1}{arg2}#m
\parallelTransport{start}{end}#m
\parallelTransport{start}{end}(arg)#m
\parallelTransport{start}{end}[sup]#*m
\parallelTransport{start}{end}(arg)[sup]#m
\parallelTransport[scale%keyvals]{start}{end}#m
\parallelTransport[scale%keyvals]{start}{end}(arg)#m
\parallelTransport[scale%keyvals]{start}{end}[sup]#*m
\parallelTransport[scale%keyvals]{start}{end}(arg)[sup]#m
\parallelTransportDir{start}{dir}#m
\parallelTransportDir{start}{dir}(arg)#m
\parallelTransportDir{start}{dir}[sup]#*m
\parallelTransportDir{start}{dir}(arg)[sup]#m
\parallelTransportDir[scale%keyvals]{start}{dir}#m
\parallelTransportDir[scale%keyvals]{start}{dir}(arg)#m
\parallelTransportDir[scale%keyvals]{start}{dir}[sup]#*m
\parallelTransportDir[scale%keyvals]{start}{dir}(arg)[sup]#m
\retract{base}#m
\retract{base}(arg)#m
\retract[scale%keyvals]{base}#m
\retract[scale%keyvals]{base}(arg)#m
\riemannian{arg1}{arg2}#m
\riemannian{arg1}{arg2}[sub]#m
\riemannian[scale%keyvals]{arg1}{arg2}#m
\riemannian[scale%keyvals]{arg1}{arg2}[sub]#m
\riemanniannorm{arg}#m
\riemanniannorm{arg}[sub]#m
\riemanniannorm[scale%keyvals]{arg}#m
\riemanniannorm[scale%keyvals]{arg}[sub]#m
\secondCovariantDerivative{arg1}{arg2}#m
\secondCovariantDerivative{arg1}{arg2}[arg]#m
\tangentSpace{point}#m
\tangentSpace{point}[manifold]#m
\tangentBundle#m
\tangentBundle[manifold]#m
\tensorBundle{arg1}{arg2}#m
\tensorBundle{arg1}{arg2}[manifold]#m
\tensorSpace{arg1}{arg2}#m
\tensorSpace{arg1}{arg2}[vector space]#m
\vectorTransport{start}{end}#m
\vectorTransport{start}{end}(arg)#m
\vectorTransport{start}{end}[sup]#*m
\vectorTransport{start}{end}(arg)[sup]#m
\vectorTransport[scale%keyvals]{start}{end}#m
\vectorTransport[scale%keyvals]{start}{end}(arg)#m
\vectorTransport[scale%keyvals]{start}{end}[sup]#*m
\vectorTransport[scale%keyvals]{start}{end}(arg)[sup]#m
\vectorTransportDir{start}{dir}#m
\vectorTransportDir{start}{dir}(arg)#m
\vectorTransportDir{start}{dir}[sup]#*m
\vectorTransportDir{start}{dir}(arg)[sup]#m
\vectorTransportDir[scale%keyvals]{start}{dir}#m
\vectorTransportDir[scale%keyvals]{start}{dir}(arg)#m
\vectorTransportDir[scale%keyvals]{start}{dir}[sup]#*m
\vectorTransportDir[scale%keyvals]{start}{dir}(arg)[sup]#m

#keyvals:\exponential#c,\logarithm#c,\inverseRetract#c,\lie#c,\parallelTransport#c,\parallelTransportDir#c,\retract#c,\riemannian#c,\riemanniannorm#c,\vectorTransport#c,\vectorTransportDir#c
big
Big
bigg
Bigg
auto
none
#endkeyvals