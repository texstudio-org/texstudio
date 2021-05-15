CREATE TABLE IF NOT EXISTS "SubFolders" (
	"Name"	TEXT NOT NULL,
	PRIMARY KEY("Name")
);end_of_query
CREATE TABLE IF NOT EXISTS "SubsubFolders" (
	"Name"	TEXT,
	PRIMARY KEY("Name")
);end_of_query
CREATE TABLE IF NOT EXISTS "Files_per_Document" (
	"Document_Id"	TEXT NOT NULL,
	"File_Id"	TEXT NOT NULL,
	FOREIGN KEY("Document_Id") REFERENCES "Documents"("Id") ON UPDATE CASCADE
);end_of_query
CREATE TABLE IF NOT EXISTS "Basic_Folders" (
	"Name"	TEXT NOT NULL,
	PRIMARY KEY("Name")
);end_of_query
CREATE TABLE IF NOT EXISTS "Document_Types" (
	"Name"	TEXT NOT NULL,
	"Description"	TEXT,
	PRIMARY KEY("Name")
);end_of_query
CREATE TABLE IF NOT EXISTS "Documents" (
	"Id"	TEXT,
	"Document_Type"	TEXT NOT NULL,
	"Basic_Folder"	TEXT NOT NULL,
	"SubFolder"	TEXT NOT NULL,
	"SubsubFolder"	TEXT,
	"Path"	TEXT,
	"Date"	TEXT,
	"Content"	TEXT,
	FOREIGN KEY("SubFolder") REFERENCES "SubFolders"("Name") ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY("Basic_Folder") REFERENCES "Basic_Folders"("Name") ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY("SubsubFolder") REFERENCES "SubsubFolders"("Name") ON UPDATE CASCADE ON DELETE CASCADE,
	PRIMARY KEY("Id"),
	FOREIGN KEY("Document_Type") REFERENCES "Document_Types"("Name") ON UPDATE CASCADE ON DELETE CASCADE
);end_of_query
CREATE TABLE IF NOT EXISTS "SubsubFolders_per_Sub_perBasic" (
	"Subsub_Id"	TEXT,
	"Sub_Id"	TEXT,
	"Basic_Id"	TEXT,
	PRIMARY KEY("Subsub_Id","Sub_Id","Basic_Id"),
	FOREIGN KEY("Subsub_Id") REFERENCES "SubsubFolders"("Name") ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY("Basic_Id") REFERENCES "Basic_Folders"("Name") ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY("Sub_Id") REFERENCES "SubFolders"("Name") ON UPDATE CASCADE ON DELETE CASCADE
);end_of_query
CREATE TABLE IF NOT EXISTS "SubFolders_per_Basic" (
	"Sub_Id"	TEXT NOT NULL,
	"Basic_Id"	TEXT NOT NULL,
	FOREIGN KEY("Basic_Id") REFERENCES "Basic_Folders"("Name") ON UPDATE CASCADE ON DELETE CASCADE,
	PRIMARY KEY("Sub_Id","Basic_Id"),
	FOREIGN KEY("Sub_Id") REFERENCES "SubFolders"("Name") ON UPDATE CASCADE ON DELETE CASCADE
);end_of_query
CREATE TRIGGER Delete_Subsub_ON_Basic
AFTER DELETE
ON Basic_Folders
BEGIN
DELETE FROM SubsubFolders WHERE Name IN (
SELECT *
FROM SubsubFolders
WHERE Name NOT IN (SELECT Subsub_Id FROM SubsubFolders_per_Sub_perBasic));
END;end_of_query
CREATE TRIGGER Delete_Subsub_ON_Sub
AFTER DELETE
ON SubFolders
BEGIN
DELETE FROM SubsubFolders WHERE Name IN (
SELECT *
FROM SubsubFolders
WHERE Name NOT IN (SELECT Subsub_Id FROM SubsubFolders_per_Sub_perBasic));
END;end_of_query
CREATE TRIGGER Delete_Sub_ON_Basic
AFTER DELETE
ON Basic_Folders
BEGIN
DELETE FROM SubFolders WHERE Name IN (
SELECT *
FROM SubFolders
WHERE Name NOT IN (SELECT Sub_Id FROM SubFolders_per_Basic));
END;end_of_query
