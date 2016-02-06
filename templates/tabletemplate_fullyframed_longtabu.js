var metaData = {
"Name"        : "Longtabu, fully framed",
"Description" : "Format table using the longtabu environonment.", 
"Author"      : "Jan Sundermeyer",
"Date"        : "6.2.2016",
"Version"     : "1.0"
}

function print(str){
cursor.insertText(str)
}
function println(str){
cursor.insertText(str+"\n")
}
//var arDef=def.split("")
var width=" to \\linewidth "
if(widthDef.length>0)
  width=widthDef
println("\\begin{longtabu}"+width+"{|"+defSplit.join("|")+"|}")
println("\\hline")
for(var i=0;i<tab.length;i++){
	var line=tab[i];
	for(var j=0;j<line.length;j++){
		print(line[j])
		if(j<line.length-1)
			print("&")
	}
	println("\\\\ \\hline")
}
println("\\end{longtabu}")
