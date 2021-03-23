/*
Install script for texstudio
*/
function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    component.createOperations();
    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/texstudio.exe", "@StartMenuDir@/TexStudio.lnk","-param");
        var iconId = 0;
        var notepadPath =  "@TargetDir@\\texstudio.exe";
        component.addOperation("RegisterFileType",
                               "tex",
                               notepadPath + " '%1'",
                               "QInstaller Framework example file type",
                               "text/plain",
                               notepadPath + "," + iconId,
                               "ProgId=TexStudio.tex" );
    }
}
