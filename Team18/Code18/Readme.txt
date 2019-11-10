1. Open up StartupSPASolution.sln on visual studio 2019 on the windows platform
2. Do a rebuild solution on StartupSPASolution
3. Right-click on "AutoTester" on the solution explorer and click set as startup project
4. Set the "release" mode
4. Go to "Debug" menu at the top, and click AutoTester Properties
5. Under Configuration properties, select "Debugging"
6. Under Command Arguments an input would be " ..\Tests18\Iteration3\sources\With_source.txt ..\Tests18\Iteration3\queries\With_queries.txt ..\Tests18\out.xml"
7. The AutoTester will run the specified queries and source file
8. The results of the AutoTester will be generated at Team18\Code18\Tests18\out.xml