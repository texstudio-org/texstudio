function print(str){
cursor.insertText(str)
}
function println(str){
cursor.insertText(str+"\n")
}
var arDef=def.split("");
if(env=="tabularx"){
  println("\\begin{tabularx}{\\linewidth}{|"+arDef.join("|")+"|}")
}else{
    println("\\begin{"+env+"}{|"+arDef.join("|")+"|}")
}
println("\\hline")
for(var i=0;i<tab.length;i++){
	var line=tab[i];
	for(var j=0;j<line.length;j++){
                var col=line[j];
                var mt=col.match(/^\\textbf/);
                if(i==0 && !mt)
                  print("\\textbf{")
		print(line[j])
                if(i==0 && !mt)
                  print("}")
		if(j<line.length-1)
			print("&")
	}
	println("\\\\ \\hline")
}
println("\\end{tabularx}")
