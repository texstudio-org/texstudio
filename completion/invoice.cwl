# invoice package
# Matthew Bertucci 2022/07/06 for v0.91

#include:ifthen
#include:longtable
#include:calc
#include:siunitx
#include:fp

#keyvals:\usepackage/invoice#c
afrikaans
dutch
english
estonian
finnish
french
german
italian
spanish
spanishe
spanishv
swedish
comma
#endkeyvals

\begin{invoice}{base currency}{VAT}
\end{invoice}

\ProjectTitle{text}
\Fee{contents%text}{rate/unit}{count}
\STFee
\EBC{contents%text}{amount}
\EFC{contents%text}{foreign currency}{amount}{conversion rate}{base currency result}
\EBCi{contents%text}{amount}
\EFCi{contents%text}{foreign currency}{amount}{conversion rate}{base currency result}
\STExpenses
\Discount{contents%text}{amount}
\STProject

\BC#*
\commafalse#S
\commatrue#S
\Flag#*
\ifcomma#S
\ifVATnonzero#S
\invoiceno{arg}#S
\InvoiceVersion#S
\Null#*
\Project#*
\theDiscount#*
\theExpenses#*
\theFee#*
\theProject#*
\theTotal#*
\theVAT#*
\VATnonzerofalse#S
\VATnonzerotrue#S

# from invoicelabels.sty
\Activity#*
\Amount#*
\Count#*
\Currency#*
\Error#*
\Expense#*
\Expenses#*
\Factor#*
\FeeBeforeExpense#S
\FeeSTExists#S
\Fees#*
\InternalError#S
\InvoiceCompleted#S
\InvoiceCompletedNoExpense#S
\InvoiceCompletedNoFee#S
\InvoiceCompletedNoFeeST#S
\InvoiceCompletedNoProject#S
\InvoiceCompletedNoProjectST#S
\KOMA#S
\MissingFee#S
\MissingInputData#S
\MissingOpening#S
\MissingProject#S
\NoInvoiceNesting#S
\NoProjectNesting#S
\ProjectCompletedNoExpense#S
\ProjectCompletedNoFee#S
\ProjectEmpty#S
\ProjectSTExists#S
\SubtotalExpenses#*
\SubtotalFee#*
\SubtotalProject#*
\SumExpenses#*
\SumFees#*
\SumVAT#*
\Total#*
\UnitRate#*
\VAT#*
\Warning#*