<%@language=jscript%>
<% title="List of CPP files" %>
<!--#include virtual="/jang/include/editfile.inc"-->
<html>
<head>
	<title><%=title%></title>
	<meta HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=big5">
	<meta HTTP-EQUIV="Expires" CONTENT="0">
	<style>
		td {font-family: "標楷體", "helvetica,arial", "Tahoma"}
		A:link {text-decoration: none}
		A:hover {text-decoration: underline}
	</style>
</head>
<script src="/jang/js/lib/utility4webClient.js"></script>

<body background="/jang/graphics/background/yellow.gif">
<font face="標楷體">
<h2 align=center><%=title%></h2>
<h3 align=center><a target=_blank href="/jang/">張智星</a></h3>
<hr>

<h3><img src="/jang/graphics/dots/redball.gif">
Basic differences from C</h3>
<ul>
<li><a target=_blank href="iostream00.cpp">iostream00.cpp</a>
<li><a target=_blank href="iostream01.cpp">iostream01.cpp</a>
<li><a target=_blank href="iostream02.cpp">iostream02.cpp</a>
<li><a target=_blank href="localVarDeclare.cpp">localVarDeclare.cpp</a>
<li><a target=_blank href="defineCplusplus.cpp">defineCplusplus.cpp</a>
<li><a target=_blank href="defaultArgument.cpp">defaultArgument.cpp</a>
<li><a target=_blank href="functionInline.cpp">functionInLine.cpp</a>
<li><a target=_blank href="staticCast01.cpp">staticCast01.cpp</a>
<li><a target=_blank href="functionOverloading.cpp">functionOverloading.cpp</a>
<li><a target=_blank href="functionTemplate.cpp">functionTemplate.cpp</a>
<li><a target=_blank href="stlString00.cpp">stlString00.cpp</a>
<li><a target=_blank href="reference.cpp">reference.cpp</a>
<li><a target=_blank href="swap.cpp">swap.cpp</a>
<li><a target=_blank href="exceptionHandling00.cpp">exceptionHandling00.cpp</a>
<li><a target=_blank href="exceptionHandling01.cpp">exceptionHandling01.cpp</a>
</ul>

<h3><img src="/jang/graphics/dots/redball.gif">
Erros in pointers and arrays</h3>
<ul>
<li><a target=_blank href="memoryLeak00.cpp">memoryLeak00.cpp</a>
<li><a target=_blank href="memoryLeak01.cpp">memoryLeak01.cpp</a>
<li><a target=_blank href="memoryLeak02.cpp">memoryLeak02.cpp</a>
<li><a target=_blank href="outOfBoundIndexing.cpp">outOfBoundIndexing.cpp</a>
</ul>

<h3><img src="/jang/graphics/dots/redball.gif">
Class and constructors</h3>
<ul>
<li><a target=_blank href="constructor00.cpp">constructor00.cpp</a>
<li><a target=_blank href="constructor01.cpp">constructor01.cpp</a>
<li><a target=_blank href="constructor02.cpp">constructor02.cpp</a>
<li><a target=_blank href="operatorOverloading.cpp">operatorOverloading.cpp</a>
<li><a target=_blank href="shallowCopy00.cpp">shallowCopy00.cpp</a>: Demo of shallow copy
<li><a target=_blank href="deepCopy00.cpp">deepCopy00.cpp</a>: Use new copy constructor to avoid shallow copy
<li><a target=_blank href="deepCopy01.cpp">deepCopy01.cpp</a>: Use new assignment operator to avoid shallow copy
<li><a target=_blank href="deepCopy02.cpp">deepCopy02.cpp</a>: Use both to avoid shallow copy
</ul>

<h3><img src="/jang/graphics/dots/redball.gif">
An example of selection sort</h3>
<ul>
<li><a target=_blank href="selsort00.cpp">selsort00.cpp</a>: Pass by value for swap(), which does not work at all
<li><a target=_blank href="selsort01.cpp">selsort01.cpp</a>: Pass by address for swap()
<li><a target=_blank href="selsort02.cpp">selsort02.cpp</a>: Pass by reference for swap()
<li><a target=_blank href="selsort03.cpp">selsort03.cpp</a>: Selection sort for vector of records (structures)
<li><a target=_blank href="selsort04.cpp">selsort04.cpp</a>: Function for record comparison
<li><a target=_blank href="selsort05.cpp">selsort05.cpp</a>: Method for record comparison
<li><a target=_blank href="selsort06.cpp">selsort06.cpp</a>: Operator overloading for record comparison
<li><a target=_blank href="selsort07.cpp">selsort07.cpp</a>: Function template for selection sort, for both structure and integer vectors
</ul>

<h3><img src="/jang/graphics/dots/redball.gif">
Examples of STL vectors</h3>
<ul>
<li><a target=_blank href="vec00.cpp">vec00.cpp</a>: Show basic use of STL vectors
<li><a target=_blank href="capacity00.cpp">capacity00.cpp</a>: Show how STL vectors perform memory allocation implicitly
<li><a target=_blank href="capacity01.cpp">capacity01.cpp</a>: Show how STL vectors perform memory allocation implicitly
<li><a target=_blank href="max_size00.cpp">max_size00.cpp</a>: Show the use size(), capacity(), and max_size()
<li><a target=_blank href="vecPrint00.cpp">vecPrint00.cpp</a>: Print STL vectors using ostream_iterator
<li><a target=_blank href="vecUnique00.cpp">vecUnique00.cpp</a>: Show the use of sort(), unique(), and erase()
<li><a target=_blank href="vecReplace00.cpp">vecReplace00.cpp</a>: Show the use of replace(), copy()
</ul>

<h3><img src="/jang/graphics/dots/redball.gif">
<a href="map">Examples of STL maps</a></h3>

<h3><img src="/jang/graphics/dots/redball.gif">
<a href="trie">Examples of tries</a></h3>

<h3><img src="/jang/graphics/dots/redball.gif">
Example of Chapter 3</h3>
<ul>
<li><a target=_blank href="gameScore00.cpp">gameScore00.cpp</a>: Storing game entries in an array
<li><a target=_blank href="ticTacToe00.cpp">ticTacToe00.cpp</a>: Game of Tic-Tac-Toe
</ul>

<hr>

<table border=0 width=100%><tr><td align=left>
<script language="JavaScript">
document.write("Last updated on " + document.lastModified + ".")
</script>
<td align=right>
</table>

<a href="/jang/include/editfile.asp?FileName=<%=Request.ServerVariables("PATH_INFO")%>"><img align=right border=0 src="/jang/graphics/invisible.gif"></a>
</font>
</body>
</html>