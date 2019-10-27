case $1 in
    1)ARG=1
      for file in ./Iteration1/sources/*_source.txt
      do
          filename=$(basename -- ${file%_source.txt})
          ../Debug/AutoTester.exe ./Iteration1/sources/${filename}_source.txt ./Iteration1/queries/${filename}_queries.txt ./Iteration1/reports/out_${filename}.xml
      done
      ;;
    2)ARG=2
      for file in ./Iteration2/sources/*_source.txt
      do
          filename=$(basename -- ${file%_source.txt})
          ../Debug/AutoTester.exe ./Iteration2/sources/${filename}_source.txt ./Iteration2/queries/${filename}_queries.txt ./Iteration2/reports/out_${filename}.xml
      done
      ;;
    3)ARG=3
      for file in ./Iteration3/sources/*_source.txt
      do
          filename=$(basename -- ${file%_source.txt})
          ../Debug/AutoTester.exe ./Iteration3/sources/${filename}_source.txt ./Iteration3/queries/${filename}_queries.txt ./Iteration3/reports/out_${filename}.xml
      done
      ;;
    all)ARG=all
      for file in ./Iteration1/sources/*_source.txt
      do
          filename=$(basename -- ${file%_source.txt})
          ../Debug/AutoTester.exe ./Iteration1/sources/${filename}_source.txt ./Iteration1/queries/${filename}_queries.txt ./Iteration1/reports/out_${filename}.xml
      done
      for file in ./Iteration2/sources/*_source.txt
      do
          filename=$(basename -- ${file%_source.txt})
          ../Debug/AutoTester.exe ./Iteration2/sources/${filename}_source.txt ./Iteration2/queries/${filename}_queries.txt ./Iteration2/reports/out_${filename}.xml
      done
      for file in ./Iteration3/sources/*_source.txt
      do
          filename=$(basename -- ${file%_source.txt})
          ../Debug/AutoTester.exe ./Iteration3/sources/${filename}_source.txt ./Iteration3/queries/${filename}_queries.txt ./Iteration3/reports/out_${filename}.xml
      done
      ;;
    *) exit 1;;
esac

