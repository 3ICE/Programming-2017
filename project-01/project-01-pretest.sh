#!/bin/zsh -f

###############################################################################

HARJOITUSTYOKERTA=project-01
HARJOITUSTYOHAKEMISTO=~/TIE-02206/${HARJOITUSTYOKERTA}
TYOHAKEMISTO=/tmp/${USER}-${HARJOITUSTYOKERTA}-$$
TESTIBINAARI=${TYOHAKEMISTO}/${HARJOITUSTYOKERTA}

OUTPUTTEST=~aps/bin/outputtest
TESTIDATA=~aps/public/${HARJOITUSTYOKERTA}-pretest-data

CIN_ECHO_LIB=~aps/public/cin_echo.o
COMPILER_OUTPUT=${TYOHAKEMISTO}/compiler-output.txt
WRAPPER=${HARJOITUSTYOKERTA}.wrapper


RM=(/bin/rm -rf)
CP=(/bin/cp -rf)
CHMOD=(/bin/chmod)

###############################################################################

zshexit() { ${RM} ${TYOHAKEMISTO} }
TRAPINT() { zshexit }

luo_wrapper_skripti() {
	cat >! ${WRAPPER} <<-EOF
	#!/bin/zsh

	limit -h cputime 5
	renice +19 $$ >/dev/null 2>&1

	 ${TESTIBINAARI} |& \
	  egrep -v '^ *$' | \
	  perl -n \
	    -e 'chomp;' \
	    -e 's/^[Ee]rror:?.*/Error: .../i;' \
	    -e 'print \$_, "\n";'
	EOF

        ${CHMOD} 770 ${WRAPPER}
}

###############################################################################

if [[ ! -d ${HARJOITUSTYOHAKEMISTO} ]]; then
   echo "Error: project folder ${HARJOITUSTYOHAKEMISTO} does not exist."
   exit 1
fi

if [[ ! -f ${HARJOITUSTYOHAKEMISTO}/${HARJOITUSTYOKERTA}.pro ]]; then
   echo "Error: project file ${HARJOITUSTYOKERTA}.pro does not exist."
   exit 1
fi


cat <<EOF
+--------------------------------------------------------------------------+
|                                                                          |
|  This program will automatically perform basic tests for your project:   |
|                                                                          |
|  - It will check that the output of your program doesn't contain         |
|    any typos or other trivial differences compared to the required       |
|    output.                                                               |
|  - It will also run some elementary tests to find out if your            |
|    behaves functionally the way the project was defined.                 |
|                                                                          |
|  These tests are by no means complete and even if your program passes    |
|  these tests it doesn't mean there are no errors in the programs.        |
|  In other words: the final responsibility for testing your project       |
|  is yours.                                                               |
|                                                                          |
|  If your program passes the test, there should only be one line          |
|  printed below this box:                                                 |
|                                                                          |
|       [[Your program PASSED the pretest]]                                |
|                                                                          |
|  Any other outputs are sign of something being wrong.                    |
|                                                                          |
+--------------------------------------------------------------------------+

EOF


umask 077


${CP} -rf ${HARJOITUSTYOHAKEMISTO} ${TYOHAKEMISTO}
${CP} -rf ${TESTIDATA}/* ${TYOHAKEMISTO}


cd ${TYOHAKEMISTO}


luo_wrapper_skripti

perl -0777 -pi -e "s{^}{LIBS += ${CIN_ECHO_LIB}\n}" ${HARJOITUSTYOKERTA}.pro


qmake-qt5 >! ${COMPILER_OUTPUT} 2>&1
make --silent >> ${COMPILER_OUTPUT} 2>&1

if [[ -s ${COMPILER_OUTPUT} ]]; then
    echo "+------------------------------------------------------------------+"
    echo "|   Error: compilation produced the following error messages       |"
    echo "+------------------------------------------------------------------+"

    cat ${COMPILER_OUTPUT}

    echo "\n"
fi

if [[ ! -f ${TESTIBINAARI} ]]; then
    echo "+------------------------------------------------------------------+"
    echo "|   Error: compilation did not produce an executable program       |"
    echo "+------------------------------------------------------------------+"
    echo "\n"

    exit 1
fi


${OUTPUTTEST} \
      --nohighlight --showdiff --timeout=3 \
      --showcorrect --showtested \
      --ignorescandinavian \
  *.outputtest ${WRAPPER} \
     | sed \
        -e '2,15d' \
        -e '/helpottamiseksi/,+5d' \
        -e 's/[·§]/ /g' \
        -e 's/outputtest:.*toimi.*oikein.*/[[Your program PASSED the pretest]]/' \
        -e 's/outputtest:.*toimi.*v..rin.*/[[Your program FAILED the pretest]]\n\nThe following keyboard input was used in this test:/' \
        -e 's/Oikein toimivan ohjelman tulosteet.*/Correctly behaving program should output:/' \
        -e 's/Testatun ohjelman tulosteet.*/Your program produced this output:/' \
        -e 's/diff-komennon tulostus testisuoritukselle/diff command between correct behaviour and your program output:/'