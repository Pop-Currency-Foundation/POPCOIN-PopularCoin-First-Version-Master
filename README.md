PopularCoin integration/staging tree
================================

http://www.Popularcoin.org

Copyright (c) 2009-2014 Bitcoin Developers 
Copyright (c) 2011-2014 Litecoin Developers 
Copyright (c) 2014 PopularCoin Developers

What is PopularCoin?
--------------------

PopularCoin is an open source currency for people to mine and trade with a team of developers that is dedicated in ethically working to raise the value for every wallet owner. What makes POP Coin Socially Innovative is how it plays on very specific words that are imprinted into our culture, POP and Popular. Keeping this in mind, our development has been and will continue to be based on a play to those words. Another example of how we will be playing on those social words is that the wallets of our future will have extensive polling and voting on ideas, issues and artwork.

For more information, as well as an immediately useable, binary version of the PopularCoin client sofware, see http://www.popularcoin.org.

License
-------

PopularCoin is released under the terms of the MIT license. See COPYING for more information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the PopularCoin development team members simply pulls it.

If it is a more complicated or potentially controversial change, then the patch submitter will be asked to start a discussion (if they haven't already) on the mailing list.

The patch will be accepted if there is broad consensus that it is a good thing. Developers should expect to rework and resubmit patches if the code doesn't match the project's coding conventions (see doc/coding.txt) or are controversial.

The master branch is regularly built and tested, but is not guaranteed to be completely stable. Tags are created regularly to indicate new official, stable release versions of PopularCoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull requests than we can review and test. Please be patient and help out, and remember this is a security-critical project where any mistake might cost people lots of money.

###Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to submit new unit tests for old code.

Unit tests for the core code are in src/test/. To compile and run them:

cd src; make -f makefile.unix test

Unit tests for the GUI code are in src/qt/test/. To compile and run them:

qmake POPCOIN_QT_TEST=1 -o Makefile.test popcoin-qt.pro
make -f Makefile.test
./popcoin-qt_test
