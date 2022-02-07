# hepparticles package
# Matthew Bertucci 2/5/2022 for v2.0

#include:amsmath
#include:subdepth

#keyvals:\usepackage/hepparticles#c
italic
#endkeyvals

\HepGenParticle{main%formula}{subscript%formula}{superscript%formula}
\HepGenAntiParticle{main%formula}{subscript%formula}{superscript%formula}

\HepParticle{main%formula}{subscript%formula}{superscript%formula}
\HepAntiParticle{main%formula}{subscript%formula}{superscript%formula}

\HepGenSusyParticle{main%formula}{subscript%formula}{superscript%formula}
\HepSusyParticle{main%formula}{subscript%formula}{superscript%formula}
\HepGenSusyAntiParticle{main%formula}{subscript%formula}{superscript%formula}
\HepSusyAntiParticle{main%formula}{subscript%formula}{superscript%formula}

\HepResonanceMassTerm{main%formula}{subscript%formula}{superscript%formula}
\HepResonanceSpecTerm{main%formula}{subscript%formula}{superscript%formula}

\HepParticleResonance{name%formula}{mass%formula}{massSub%formula}{massSup%formula}
\HepParticleResonanceFull{main%formula}{sub%formula}{sup%formula}{mass%formula}{massSub%formula}{massSup%formula}
\HepParticleResonanceFormal{mass%formula}{massSub%formula}{massSup%formula}{spec%formula}{specSub%formula}{specSup%formula}
\HepParticleResonanceFormalFull{main%formula}{sub%formula}{sup%formula}{mass%formula}{massSub%formula}{massSup%formula}{spec%formula}{specSub%formula}{specSup%formula}

\HepProcess{iParticles \to fParticles%formula}

\filedate#S
\fileversion#S