# rigidnotation package
# Matthew Bertucci 2024/05/14 for v1.0.0

#include:mathtools

\NewRigidNotation{name}{symbol}
\SetConciseNotation{bool}
\UnsetConciseNotation

\Tran#m
\Inv#m
\Herm#m
\Conj#m

\Pos%<[accent]{subj}{basis}{coord}%>#m
\Rot%<[accent]{subj}{basis}{coord}%>#m
\Pose%<[accent]{subj}{basis}{coord}%>#m