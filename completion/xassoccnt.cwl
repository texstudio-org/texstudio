# xassoccnt package
# Matthew Bertucci 11/26/2021 for v2.0

### 2 Requirements, loading and incompatibilities
#include:etoolbox
#include:letltxmacro
#include:xcolor
#include:l3keys2e

#keyvals:\usepackage/xassoccnt#c
autodefinecounters#true,false
nonumberofruns
redefinelabel#true,false
standardcounterformats=#on,off
#endkeyvals

### 3 Additions and extensions to standard counter related commands
\addtocounter{counter}{value}[options%keyvals]

#keyvals:\addtocounter
wrap#true,false
#endkeyvals

\NewDocumentCounter{counter1,counter2,...}
\NewDocumentCounter{counter1,counter2,...}[resetting counter]#*
\NewDocumentCounter[options%keyvals]{counter1,counter2,...}
\NewDocumentCounter[options%keyvals]{counter1,counter2,...}[resetting counter]#*
\DeclareDocumentCounter{counter1,counter2,...}
\DeclareDocumentCounter{counter1,counter2,...}[resetting counter]#*
\DeclareDocumentCounter[options%keyvals]{counter1,counter2,...}
\DeclareDocumentCounter[options%keyvals]{counter1,counter2,...}[resetting counter]#*

#keyvals:\NewDocumentCounter,\DeclareDocumentCounter
initial=%<integer%>
#endkeyvals

\SetDocumentCounter{counter}{value}
\SetDocumentCounter[options%keyvals]{counter}{value}

#keyvals:\SetDocumentCounter
associatedtoo#true,false
onlycounters=%<counter list%>
#endkeyvals

\StepDownCounter{counter}
\SubtractFromCounter{counter}{delta value}
\CopyDocumentCounters{source counter}{target counter}
\SwapDocumentCounters{counter1}{counter2}
\SyncCounters{driver counter}

\IfIsDocumentCounterTF{name}{true}{false}
\IfIsDocumentCounterT{name}{true}
\IfIsDocumentCounterF{name}{false}

\LastAddedToCounter
\LastSteppedCounter
\LastRefSteppedCounter
\LastSetCounter
\LastCounterValue

### 4 Counter reset lists
\RemoveFromReset{counter1,counter2,...}{driver counter}
\RemoveFromFullReset{counter1,counter2,...}{driver counter}
\ClearCounterResetList{driver counter}
\ClearCounterResetList*{driver counter}
\AddToReset{counter1,counter2,...}{driver counter}

\countersresetlistcount{counter}
\getresetlistcount
\CounterFullResetList{counter}

\IfInResetListTF{resetting counter}{counter}{true}{false}
\IfInResetListT{resetting counter}{counter}{true}
\IfInResetListF{resetting counter}{counter}{false}
\DisplayResetList{resetting counter}
\DisplayResetList[separator]{resetting counter}
\ShowResetList{resetting counter}
\GetAllResetLists
\GetParentCounter{counter}

### 5 Performing the same action for many counters
\LoopAddtoCounters{counter1,counter2,...}{increment}
\LoopResetCounters{counter1,counter2,...}
\LoopRefstepCounters{counter1,counter2,...}
\LoopSetCounters{counter1,counter2,...}{value}
\LoopStepCounters{counter1,counter2,...}
\LoopCountersFunction{counter1,counter2,...}{macro}
\LoopCounterResetList{counter}{macro}
\LoopFullCounterResetList{counter}{macro}
\CounterWithin{counter1,counter2,...}{driver counter}
\CounterWithin*{counter1,counter2,...}{driver counter}
\CounterWithout{counter1,counter2,...}{driver counter}
\CounterWithout*{counter1,counter2,...}{driver counter}

### 6 Counter output
\BinaryValue{counter}
\hexValue{counter}
\HexValue{counter}
\OctalValue{counter}
\xalphalph{counter}
\xAlphAlph{counter}

\CounterFormat{counter1!format1,counter2!format2,...}
\CounterFormat[options%keyvals]{counter1!format1,counter2!format2,...}

#keyvals:\CounterFormat
recursive#true,false
separator=%<character%>
#endkeyvals

\StoreCounterFormats{shorthand1!macro1,shorthand2!macro2,...}
\StoreCounterFormats[options%keyvals]{shorthand1!macro1,shorthand2!macro2,...}
\AddCounterFormats{shorthand1!macro1,shorthand2!macro2,...}
\AddCounterFormats[options%keyvals]{shorthand1!macro1,shorthand2!macro2,...}

#keyvals:\StoreCounterFormats,\AddCounterFormats
separator=%<character%>
#endkeyvals

\RemoveCounterFormats{shorthand1,shorthand2,...}

### 7 Associated counters
\DeclareAssociatedCounters{driver counter}{assoc counter list}
\DeclareAssociatedCounters[options%keyvals]{driver counter}{assoc counter list}
\AddAssociatedCounters{driver counter}{assoc counter list}
\AddAssociatedCounters[options%keyvals]{driver counter}{assoc counter list}

#keyvals:\DeclareAssociatedCounters,\AddAssociatedCounters
autodefine=#none,all,driver,associated
sloppy
#endkeyvals

\RemoveAssociatedCounter{driver counter}{assoc counter}
\RemoveAssociatedCounters{driver counter}{assoc counter list}
\ClearAssociatedCounters{driver counter}
\DeclareTotalAssociatedCounters{driver counter}{assoc counter list}

\AddDriverCounter{driver counter}
\RemoveDriverCounter{driver counter}
\ClearDriverCounters

\IsAssociatedToCounter{driver counter}{assoc counter}{true}{false}
\GetDriverCounter{counter}
\IsAssociatedCounter{counter}{true}{false}
\IsDriverCounter{driver counter}{true}{false}

### 8 Backup and restore of counter values
# currently disabled

### 9 Coupled counters
\DeclareCoupledCounters{counter1,counter2,...}
\DeclareCoupledCounters[options%keyvals]{counter1,counter2,...}

#keyvals:\DeclareCoupledCounters,\AddCoupledCounters
name=%<group name%>
multiple#true,false
#endkeyvals

\DeclareCoupledCountersGroup{group name}
\RemoveCoupledCounters{counter1,counter2,...}
\RemoveCoupledCounters[options%keyvals]{counter1,counter2,...}

#keyvals:\RemoveCoupledCounters,\ClearCoupledCounters
name=%<group name%>
#endkeyvals

\AddCoupledCounters{counter1,counter2,...}
\AddCoupledCounters[options%keyvals]{counter1,counter2,...}
\ClearCoupledCounters{options%keyvals}
\ClearAllCoupledCounters
\IsCoupledCounterTF{counter}{true}{false}
\IsCoupledCounterT{counter}{true}
\IsCoupledCounterF{counter}{false}

### 10 Periodic counters
\DeclarePeriodicCounter{counter}{threshold value}
\AddPeriodicCounter{counter}{threshold value}
\RemovePeriodicCounter{counter}
\RemovePeriodicCounter{counter}
\RemoveAllPeriodicCounters
\RemoveAllPeriodicCounters[options%keyvals]
\ChangePeriodicCounterCondition{counter}{threshold value}
\ChangePeriodicCounterCondition[options%keyvals]{counter}{threshold value}

#keyvals:\RemovePeriodicCounter,\RemoveAllPeriodicCounters,\ChangePeriodicCounterCondition
reset#true,false
#endkeyvals

\IsPeriodicCounterTF{counter}{true}{false}
\IsPeriodicCounterT{counter}{true}
\IsPeriodicCounterF{counter}{false}

### 11 Suspending and resuming (associated) counters
\SuspendCounters{counter1,counter2,...}
\CascadeSuspendCounters{counter1,counter2,...}
\ResumeSuspendedCounters{counter1,counter2,...}
\ResumeAllSuspendedCounters

\IsSuspendedCounter{counter}{true}{false}

### 12 Total counters
\RegisterTotalDocumentCounter{total counter}
\RegisterTotalDocumentCounter[options%keyvals]{total counter}

#keyvals:\RegisterTotalDocumentCounter,\NewTotalDocumentCounter,\DeclareTotalDocumentCounter
supertotal#true,false
#endkeyvals

\TotalCounterInternalName{counter}
\TotalCounterInternalNameExp{counter}
\TotalValue{counter}

\IsTotalCounterTF{counter}{true}{false}
\IsTotalCounterT{counter}{true}
\IsTotalCounterF{counter}{false}

### 13 Super total counters
\NewTotalDocumentCounter{total-counter1,total-counter2,...}
\NewTotalDocumentCounter[options%keyvals]{total-counter1,total-counter2,...}
\DeclareTotalDocumentCounter{total-counter1,total-counter2,...}
\DeclareTotalDocumentCounter[options%keyvals]{total-counter1,total-counter2,...}

\IsSuperTotalCounterTF{counter}{true}{false}
\IsSuperTotalCounterT{counter}{true}
\IsSuperTotalCounterF{counter}{false}

### 14 Experimental features
\label{key}[options%keyvals]#*l
\label[cleveref overrule]{key}[options%keyvals]#*l

#keyvals:\label#c
all#true,false
select=%<counter list%>
prefix=%<string%>
prefix-sep=%<string%>
#endkeyvals

\LaTeXLabel{key}#*l
\LaTeXLabel[cleveref overrule]{key}#*l

\RegisterPreLabelHook{cmd1,cmd2,...}#*
\RegisterPostLabelHook{cmd1,cmd2,...}#*
\ClearPostLabelHook#*
\ClearPreLabelHook#*

### not documented
\AddBackupCounters[options]{arg}#*
\AddFeature[options]{arg}#*
\AddLanguageMappings{arg1}{arg2}#*
\AssignBackupCounters[options]{arg}#*
\AssociatedCounterInfoColor#*
\BackupCounterGroup[options]{arg}#*
\BackupCounterValues[options]{arg}#*
\ClearBackupCounterGroups[options]{arg}#*
\ClearBackupState[options]{arg}#*
\ClearCounterBackupState[options]{arg1}{arg2}#*
\ClearCounterFormats#*
\DeclareBackupCountersGroupName{arg}#*
\DeclareLanguageMappings{arg1}{arg2}#*
\DeclareLanguageMap{arg}#*
\DeleteBackupCounterGroups[options]{arg}#*
\DriverCounterInfoColor#*
\EnableNumberofrunsTF{arg1}{arg2}#*
\GeneralCounterInfoColor#*
\GetParentCounterChain{arg}#*
\IfExistsDriverCounterList{name}{true}{false}#*
\IsBackupCounterF{name}{false}#*
\IsBackupCounterGroupF{name}{false}#*
\IsBackupCounterGroupTF{name}{true}{false}#*
\IsBackupCounterGroupT{name}{true}#*
\IsBackupCounterTF{name}{true}{false}#*
\IsBackupCounterT{name}{true}#*
\IsBackupStateF{name}{false}#*
\IsBackupStateTF{name}{true}{false}#*
\IsBackupStateT{name}{true}#*
\NewContainer{name}#*
\NewCounterHierarchy[options]{name}#*
\PrettyPrintCounterName{arg1}{arg2}#*
\ProvideOriginalLabelCommands#*
\RedefineLabelCommand#*
\RemoveCountersFromBackupGroup[options]{arg}#*
\RemoveFeature[options]{arg}#*
\RestoreBackupCounterGroup[options]{arg}#*
\RunLabelHooks{arg}#*
\RunPostLabelHooks{arg}#*
\RunPreLabelHooks{arg}#*
\ShowAllAssociatedCounters#*
\ShowAssociatedCountersList{arg}#*
\ShowCounterFormats#*
\ShowDriverCounterList#*
\ShowLanguageMappings{arg}#*
\ShowSuspendedCounters#*
\TotalCounterInfoColor#*
\WriteCountersAtEnd#*
\showresetlist{arg}#*

\AlphAlphinternal{arg}#S
\alphalphinternal{arg}#S
\CheckIfNotPackageLoadedF#S
\CheckIfNotPackageLoadedTF#S
\CheckIfNotPackageLoadedT#S
\CheckIfPackageLoadedF#S
\CheckIfPackageLoadedTF#S
\CheckIfPackageLoadedT#S
\FormerAddBackupCounter[options]{arg}#S
\FormerBackupCounterValues[options]{arg}#S
\FormerRemoveBackupCounterInternal*{arg}#S
\FormerRemoveBackupCounterInternal{arg}#S
\FormerRemoveBackupCounters*{arg}#S
\FormerRemoveBackupCounters{arg}#S
\FormerRestoreAllCounterValues[options]#S
\FormerRestoreCounterValues[options]{arg}#S
\ifexplversionnew#S
\explversionnewtrue#S
\explversionnewfalse#S
\xassoccntpackageversion#S