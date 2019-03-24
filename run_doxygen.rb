require 'io/console'

system 'doxygen ./doxygen.cfg'
print 'Press any key to terminate...'
STDIN.getch