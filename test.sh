# MINISHELL-TESTER
RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"
function exec_test()
{
    TEST1=$(./minishell -c "$@" 1>&2)
    ES_1=$?
    TEST2=$(echo $@ "; exit" | bash 1>&2)
    ES_2=$?
	printf "$ES_1\n"
	printf "$ES_2\n"
    if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
        printf " $BOLDGREEN%s$RESET" "✓ "
    else
        printf " $BOLDRED%s$RESET" "✗ "
    fi
    printf "$CYAN \"$@\" $RESET"
    if [ "$TEST1" != "$TEST2" ]; then
        echo
        echo
        printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
        printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
    fi
    if [ "$ES_1" != "$ES_2" ]; then
        echo
        echo
        printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
        printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
    fi
    echo
    sleep 0.1
}

echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#.,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@(....,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@ M I N I S H E L L @@@@@@@,.#@@@@@@@@@@@@@@@@@@@@@........@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*....@@@@@@@@@@@@@@@@@@.........,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#......#@@@@@@@@@@@@@&.........../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.........@@@@@@@@@@..............@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...........@@@@@*................@@@@@@@@@@@ T E S T E R @@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&.............,...................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.................................@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@/,%@@@@@@@@@@.................................%@@@@&&#,...........@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@/................(@@%,......,,%@@@(............................@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@,...........(@/....................*@@,.....................*@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@........,@(...........................(@,.................@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@......@(../@@@&&&@@@@@#................,@...............@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@*...@@@,................,%@%............@,.........../@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@,..../@%........(&@@(.....(@@,........@..........,@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@&@&..................,@@%...&(.......,@..........*@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@&/*.......@/##(...................................&#..............*@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@&....@&...............,@%.......................,@...................,@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@%...       ..,/..@/..............*@..........@.........................#@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@%&      *     @@,@   &(..  *  ................@.....................,@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@*       *|*    (&@         #|#      @*........@*................@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@&              @,@                   @.........&#............@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@%            @,..@                @*.........(%........@@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@#.   ,(@@*,....,@%          *@(...........%%..........#@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@*@.......@*..........,(&@#(,.....#&........%(..............,@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@(..@#///,.#%...................,@@/.........#%@@%.................&@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@......&*....@/.......,/(*....................,@*..........*@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@,.....(&..@&...................................&*......@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@.......(*.....................................@*..%@@@@@@@@@@@@@@@@@@@@@@"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@...*&@@@@@@@@@&@@@@@@..."
#subject
exec_test "echo fo"
exec_test '/bin/ls'
exec_test "/bin/ls -laF"
exec_test '/bin/ls -l -a -F'
exec_test "exit"
exec_test 'echo "It works"'
exec_test "cd /absolute/path/of/your/choice"
exec_test "echo "/bin/pwd"
exec_test 'cd relative/path/of/your/choice'
exec_test "cd"
exec_test "echo avui"
exec_test '/bin/pwd'
exec_test "echo "cd -"
exec_test '/bin/pwd'
exec_test "cd ~/path/of/your/choice"
exec_test '/bin/pwd'
exec_test "/bin/pwd"
exec_test 'env'
exec_test "export hola=proba"
exec_test 'export gat ; unset gat'
exec_test 'export gats=33'
exec_test "echo $hola"
exec_test '/usr/bin/env'
exec_test 'ls'
exec_test "unset PATH" 
exec_test "ls"
exec_test '/bin/ls'
exec_test '/usr/bin/env'
#exec_test '/usr/local/bin/emacs'
exec_test "/bin/ls -l -A"
exec_test 'cat hola'
exec_test 'echo'
exec_test 'echo bonjour'
exec_test 'echo lalalala lalalalal alalalalal alalalala'
exec_test 'echo lalalala                lalalalal      alalalalal alalalala'
exec_test 'echo Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur.'
exec_test 'echo -n'
exec_test 'echo -n bonjour'
exec_test 'echo -n lalalala lalalalal alalalalal alalalala'
exec_test 'echo -n lalalala                lalalalal      alalalalal alalalala'
exec_test 'echo bonjour -n'
exec_test 'echo -n bonjour -n'
exec_test '                        echo                     bonjour             je'
exec_test '                        echo       -n            bonjour             je'
exec_test 'echo a '' b '' c '' d'
exec_test 'echo a "" b "" c "" d'
exec_test 'echo -n a '' b '' c '' d'
exec_test 'echo -n a "" b "" c "" d'
exec_test 'echo '' '' '''
exec_test 'export PATH='/bin:/usr/bin'; Echo bonjour'
exec_test 'export PATH='/bin:/usr/bin'; eCho bonjour'
exec_test 'export PATH='/bin:/usr/bin'; ecHo bonjour'
exec_test 'export PATH='/bin:/usr/bin'; echO bonjour'
exec_test 'export PATH='/bin:/usr/bin'; EchO bonjour'
exec_test 'export PATH='/bin:/usr/bin'; eCHo bonjour'
exec_test 'export PATH='/bin:/usr/bin'; EcHo bonjour'
exec_test 'export PATH='/bin:/usr/bin'; eChO bonjour'
exec_test 'export PATH='/bin:/usr/bin'; eChO -e 'bonjo\nur''
exec_test '-n -n -n -n bonjour'
exec_test 'echo -nnnnnnnnnnnnnnnnnnnnn bonjour'
exec_test "echo -nnn -nn hola"
exec_test 'echop -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n'
exec_test 'hola echo -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n'
exec_test 'echo echop -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n'
exec_test 'echo $?'
exec_test 'echo $?'
exec_test 'cd ../../../../../.. ; pwd'
exec_test 'echo tetera | cat -e'
exec_test 'echo 2 > out1 >> out2'
exec_test 'echo bonjour >>> test'
exec_test '$'
exec_test 'echo "\n \n \\n"'
 # CD TESTS
 exec_test 'cd .. ; pwd'
 exec_test 'cd /Users ; pwd'
 exec_test 'cd ; pwd'
 exec_test 'mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd'
 exec_test 'cd fsdfd'
 exec_test 'cd marsu'
 exec_test 'cd ../../../../../..'
 exec_test 'cd /home/user42/'
 exec_test 'cd $HOME/Bureau'
 exec_test 'unset HOME'
 exec_test 'unset HOME'
 exec_test 'cd too many arguments'
 exec_test 'cd -'
 exec_test 'cd home/.. avec CDPATH set à /'
 exec_test 'cd ~'
 exec_test 'cd .'
 exec_test 'cd'
 
# PIPE TESTS
 exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
 exec_test 'cat | cat | ls'
 exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
 exec_test 'cat /dev/random | head -c 100 | wc -c'
# exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
# exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
 # ENV EXPANSIONS + ESCAPE
 exec_test "echo $TEST"
 exec_test "echo "$TEST""
 exec_test "echo '$TEST'"
 exec_test 'echo "$TEST$TEST$TEST"'
 exec_test 'echo "$TEST$TEST=lol$TEST"'# exec_test 'echo "   $TEST lol $TEST"'
 exec_test 'echo $TEST$TEST$TEST'
 exec_test 'echo $TEST$TEST=lol$TEST""lol'
 exec_test 'echo    $TEST lol $TEST' exec_test 'echo test "" test "" test'
 exec_test 'echo "\$TEST"'
 exec_test 'echo "$=TEST"'
 exec_test 'echo "$"'
 exec_test 'echo "$?TEST"'
 exec_test 'echo $TEST $TEST'
 exec_test 'echo "$1TEST"'
 exec_test 'echo "$HOME$?$"'
 exec_test 'echo "hola$HOME$HOME que tal$?$$fruitaamb$HOME$caldillo"'
 exec_test 'echo "$"'
 exec_test 'echo "$$"'
 exec_test 'echo "$$$$$"'
 exec_test 'echo "$$$HOME$$"'
 exec_test 'echo "$$$?$$"'
 exec_test 'echo "$$$$$HOME"'
 ENV EXPANSIONS
 exec_test 'export ='
 exec_test 'export 1TEST= '  
 exec_test 'export TEST' 
 exec_test 'export ""=""' 
 exec_test 'export TES=T=""' 
 exec_test 'export TEST=LOL ; echo $TEST' 
 exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
 exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST' 
 exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS' 
 # REDIRECTIONS
 exec_test 'echo test > ls ; cat ls'
 exec_test 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
 exec_test '> lol echo test lol; cat lol'
 exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
 exec_test 'cat < ls'
 exec_test 'cat < ls > ls'
# # MULTI TESTS
 exec_test 'echo testing multi ; echo "test 1 ; | and 2" ; cat tests/lorem.txt | grep Lorem'
# # SYNTAX ERROR
 exec_test ';; test'
 exec_test '| test'
#<<<<<<< HEAD
 exec_test 'echo > <'
exec_test '|'
 exec_test '<'
# # EXIT
 exec_test "exit"
 exec_test "exit 42 53 68"
 exec_test "exit 259"
 exec_test "exit 45672"
 exec_test "exit -45672"
 exec_test "exit 9223372036854775807"
 exec_test "exit -9223372036854775808"
 exec_test "exit 9223372036854775808"
 exec_test "exit -9223372036854775810"
 exec_test "exit -4"
 exec_test "exit a 4"
 exec_test "exit 4 4"
 exec_test "exit 4 a"
 exec_test "exit wrong"
 exec_test "exit wrong_command"
 exec_test "gdagadgag"
 exec_test "ls -Z"
 exec_test "cd gdhahahad"
 exec_test "ls -la | wtf"
 exec_test "ls -la | wtf | wc"
 exec_test "ls -la | echo hola | wc"
 exec_test "wtd | echo echo | wc"
 exec_test "ls | echo echo | wc > fet | echo $$ | echo $?"
 exec_test "echo hola > proba | wc"
 exec_test "cd random_cmd ; cd $?"
 exec_test "./file_that_is_not_an_executable"
 exec_test "cat bla"
 exec_test "export test=a ; echo $test"
 exec_test "ls bonjour ; echo $?"
 exec_test "cat | cat | cat | ls"
 exec_test "<a cat <b <c"
 exec_test "export var="  truc"; echo $var"
 exec_test "unset HOME ; cd"
 exec_test "unset HOME ; cd ~"
 exec_test "export HOME="hola" ; cd"
 exec_test "export HOME="hola" ; cd ~"
 exec_test "cat <"1""2""3""4""5""
 exec_test "cat <missing"
 exec_test "echo <123 <456 hi | echo 42"
 exec_test "cat <minishell.h|ls"
