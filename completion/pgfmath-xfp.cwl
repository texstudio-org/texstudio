# pgfmath-xfp package
# Matthew Bertucci 2024/12/21 for v1.0

#include:pgfmath

\pgfmxfpdeclarefunction{name}{args}{fp expression}
\pgfmxfpdeclarefunction{name}{args}[process-args]{fp expression}

\pgfmxfpDate#S
\pgfmxfpVersion#S

# expl3 interface
\pgfmxfp_declare:nnn {%<⟨name⟩%>} {%<⟨arg count⟩%>} {%<⟨fp expr⟩%>}#/%expl3
\pgfmxfp_declare_processed_args:nnnn {%<⟨name⟩%>} {%<⟨arg count⟩%>} {%<⟨processed args⟩%>} {%<⟨fp expr⟩%>}#/%expl3