var metaData = {
"Name"        : "Colored rows",
"Description" : "Formats the table using alternate colors for rows. <br> <code>\\usepackage[table]{xcolor}</code> is necessary.", 
"Author"      : "Jan Sundermeyer",
"Date"        : "4.9.2011",
"Version"     : "1.0"
}

function print(str){
cursor.insertText(str)
}
function println(str){
cursor.insertText(str+"\n")
}
var arDef=def.split("")
println("% \\usepackage[table]{xcolor} is necessary !")
println("\\rowcolors{1}{gray!30}{gray!10}")
println("\\begin{tabular}{"+arDef.join("")+"}")
for(var i=0;i<tab.length;i++){
	var line=tab[i];
	for(var j=0;j<line.length;j++){
		print(line[j])
		if(j<line.length-1)
			print("&")
	}
	println("\\\\")
}
println("\\end{tabular}")
