var metaData = {
"Name"        : "Fully framed, first bold",
"Description" : "First line of the table is bold to mark headings.", 
"Author"      : "Jan Sundermeyer",
"Date"        : "6.2.2016",
"Version"     : "1.1"
}

function print(str){
cursor.insertText(str)
}
function println(str){
cursor.insertText(str+"\n")
}
//var arDef=def.split("");
if(env=="tabu" || env=="longtabu"){
  println("\\begin{"+env+"}"+widthDef+"{|"+defSplit.join("|")+"|}")
}else{
  if(env=="tabularx"){
    println("\\begin{tabularx}{\\linewidth}{|"+defSplit.join("|")+"|}")
  }else{
      println("\\begin{"+env+"}{|"+defSplit.join("|")+"|}")
  }
}
println("\\hline")
for(var i=0;i<tab.length;i++){
	var line=tab[i];
	if(line!="\\hline"){
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
}
println("\\end{"+env+"}")
