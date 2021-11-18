# myfilist package
# Matthew Bertucci 11/17/2021 for v0.71

#include:readprov

\EmptyFileList
\EmptyFileList[file list]
\ListInfos
\ListInfos[%<filename%>.txt]
\ListGenerator
\NoStopListInfos
\VarListInfos
\VarListInfos[%<filename%>.txt]
\WriteFileInfosTo{txt file}
\ReadListFileInfos{tex file list}
\ReadListFileInfos[txt file]{tex file list}
\UseFindUtility
\FindReadListFileInfos{tex file list}
\FindReadListFileInfos[txt file]{tex file list}
\FileListRemark{file}
\FileListRemark[info]{file}
\NoBottomLines