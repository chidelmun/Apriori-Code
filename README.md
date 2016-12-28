                                                                       FPGROWTH ALGORTHM

[![Build Status](https://travis-ci.org/chidelmun/Data-Mining-A-Priori-Algorithm.svg?branch=master)](https://travis-ci.org/chidelmun/Data-Mining-A-Priori-Algorithm)

Copyright (c) <2015> <DELVERI MUNANG, Department of Computer Engineering, University of Buea>
    
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


#What is FP Growth Algorithm

FP-growth is a program for frequent item set mining, a data mining method that was originally developed for market basket analysis. Frequent item set mining aims at finding regularities in the shopping behavior of the customers of supermarkets, mail-order companies and online shops. In particular, it tries to identify sets of products that are frequently bought together. Once identified, such sets of associated products may be used to optimize the organization of the offered products on the shelves of a supermarket or the pages of a mail-order catalog or web shop, may give hints which products may conveniently be bundled, or may allow to suggest other products to customers. However, frequent item set mining may be used for a much wider variety of tasks, which share that one is interested in finding regularities between (nominal) variables in a given data set. For an overview of frequent item set mining in general and several specific algorithms (including FP-growth).

This implementation covers the basic scheme as developed in [Han et al. 2000], which introduced the FP-tree as the core data structure. It also supports filtering for closed and maximal item sets with conditional item set repositories as suggested in [Grahne and Zhu 2003], although the approach used in the program differs in as far as it used top-down prefix trees rather than FP-trees. 



##Getting Started: Compilation and Installation

From the project's root directory ../PROJECT_ROOT

cd fpgrowth/src/;
make;

<-- To install the program -->
Run
sudo make install | su -; make install;

./fpgrowth    <-- This executes the code -->

Cleaning the fpgrowth/src/directory, run
make clean;


###Documentation

**Program Invocation
FP-growth implementation is a command line program that has to be called in a terminal or command window or from a shell script. If double-clicked in a file manager (e.g. in Microsoft Windows), it merely prints a usage message to a terminal/command window that is briefly opened and immediately closed again. This does not mean that the program does not work. In order to run the program, open a terminal/command window, change directory to where you stored the program, and then type an invocation command.

The general syntax of the program invocation is

fpgrowth [options] infile [outfile]

The first argument infile, which is mandatory, is the name of a file that contains the transactions to analyze. The format of this file is described in this section. If instead of a file name a single minus sign "-" or an empty string "" is given, the input is read from standard input rather than from a file.

The second argument outfile, which is optional (as indicated by the brackets), is the name of a file to which the found frequent item sets are to be written. That it is optional is useful for benchmark tests, where the time it takes to write the output to a file can conceal the actual search time, or if only a pattern spectrum (number of found frequent item sets collected by size and (absolute) support; option -P) is to be found. The format in which frequent item sets are written to the output file is described in this section. If instead of a file name a single minus sign "-" or an empty string "" is given, the output is written to standard output rather than to a file.

In addition to the input and output file several options can be given, all of which consist of a minus sign and a single letter. The full list of options can be found in the next section.

Some options take a parameter. For example, the option -s, with which the minimum support is specified, takes a number as a parameter, which must follow the letter s without any separating space. A space between the option character and its parameter is only allowed if the parameter is a string, for example, a file name. (However, even in this case the parameter may follow the option letter directly.) If the parameter is a number or a single letter, it must follow the option letter directly.

Options may be combined. For example,

fpgrowth -s10m2n5 input output

means that the minimum support is 10% (option -s), the minimum number of items in an item set is 2 (option -m) and the maximum number of items in an item set is 5 (option -n).

Options may be specified anywhere on the command line, that is, before the input file name, in between the input and output file names, or after the output file name.

If an option is given more than once, the last statement counts. That is, with

fpgrowth -s10 -s20 input output

the minimum support is 20%, as the -s10 is overwritten by the following -s20.

**Program Options
 FP-growth implementation supports the following options
(a # after the option letter means that the option takes a parameter):

option	meaning	                                                       default
-t#	target type
	s: frequent item sets
	c: closed (frequent) item sets
	m: maximal (frequent) item sets
	g: (frequent) generators
	r: association rules	                                         s

-m#	minimum number of items per item set                             1

-n#	maximum number of items per item set	                      no limit

-s#	minimum support of an item set
	positive: percentage of transactions
	negative: absolute number of transactions	                 10

-S#	maximum support of an item set
	positive: percentage of transactions
	negative: absolute number of transactions	                  100
	-o	use original definition of the support of a rule (body & head)	

-c#	minimum confidence of a rule as a percentage	                 80

-e#	additional evaluation measure
	frequent item sets:
	x: no measure
	b: binary logarithm of support quotient (+)
	association rules:
	x: no measure
	o: rule support (original def.: body & head) (+)
	c: rule confidence (+)
	d: absolute confidence difference to prior (+)
	l: lift value (confidence divided by prior) (+)
	a: absolute difference of lift value to 1 (+)
	q: difference of lift quotient to 1 (+)
	v: conviction (inverse lift for negated head) (+)
	e: absolute difference of conviction to 1 (+)
	r: difference of conviction quotient to 1 (+)
	z: certainty factor (relative confidence change) (+)
	n: normalized χ2 measure (+)
	p: p-value from (unnormalized) χ2 measure (-)
	y: normalized χ2 measure with Yates' correction (+)
	t: p-value from Yates-corrected χ2 measure (-)
	i: information difference to prior (+)
	g: p-value from G statistic/information difference (-)	
	f: Fisher's exact test (table probability) (-)
	h: Fisher's exact test (χ2 measure) (-)
	m: Fisher's exact test (information gain) (-)
	s: Fisher's exact test (support) (-)

All measures for association rules are also applicable
to item sets and are then aggregated over all possible
association rules with a single item in the consequent.
The aggregation mode can be set with the option -a#.
Measures marked with (+) must meet or exceed the threshold,
measures marked with (-) must not exceed the threshold
in order for the rule or item set to be reported.	x

-a#	aggregation mode for evaluation measure
	x: no aggregation (use first value)
	m: minimum of individual measure values
	n: maximum of individual measure values
	a: average of individual measure values
	s: split item set into equal size subsets	x

-d#	threshold for additional evaluation measure
	(as a percentage)	10

-p#	(minimum size for) pruning with evaluation
	< 0: weak forward
	> 0: strong forward
	= 0: backward pruning	no pruning

-q#	sort items w.r.t. their frequency
	0: do not sort
	1: ascending, -1: descending w.r.t. item frequency
	2: ascending, -2: descending w.r.t. transaction size sum	2

-A#	variant of the FP-growth algorithm to use
	s: simple tree nodes with only successor and parent
	c: complex tree nodes with children and siblings
	d: top-down processing on a single prefix tree
	t: top-down processing of the prefix trees

Variant d does not support mining closed/maximal item sets,
variant t does not support the use of a k-items machine, and
only variant c supports item reordering w.r.t. conditional support,
but closed/maximal item sets can only be mined without reordering.	c
	-x	do not prune with perfect extensions	prune

-l#	number of items for k-items machine
	(only for algorithm variants i,r,o)	16

-i	do not sort items w.r.t. cond. support
(only for algorithm variant c, option -Ac)	

-u	do not use head union tail (hut) pruning
(only for maximal item sets, not with algorithm variant b)	use hut

-F#:#..	support border for filtering item sets
(list of minimum support values, one per item set size,
starting at the minimum size, as given with option -m#)	none

-R#	read an item selection from a file
	parameter: file name	

-P#	write a pattern spectrum to a file
	parameter: file name	

-Z	print item set statistics
	(number of item sets per size)	
	-g	write output in scanable form
	(quote certain characters)	

-h#	record header for output	""

-k#	item separator for output	" "

-I#	implication sign for association rules	" "

-v#	output format for item set information
	(changed to " (%a)" if parameter of -s is negative)	" (%S)"
	" (%a)"

-w	transaction weight in last field	only items

-r#	record/transaction separators	"\n"

-f#	field/item separators	" \t,"

-b#	blank characters	" \t\r"

-C#	comment characters	"#"

-!	print additional option information	


**Input Format
Format of the Transactions File

The transactions file has to be a (text) file structured by field and record separators and blanks. Record separators, not surprisingly, separate records, usually lines (since the default record separator is the newline character), field separators separate fields, usually words (since among the default field separators are the space and the tabulator, but also the comma). Blanks are used to fill fields, for example, to align them. In the transactions file each record must contain one transaction, i.e. a list of item identifiers, which are separated by field separators. An empty record is interpreted as an empty transaction. That is, it is counted for the total number of transactions, but does not count for the support of any item set other than the empty set. A transaction may contain the same item multiple times (that is, duplicate items do not raise an error), but this multiplicity is disregarded by the FP-Growth program. It only considers whether an item is contained in a transaction or not, not how many times an item is contained in a transaction.

Example input files can be found in the directory fpgrowth/ex in the source package. These files are used in the following to demonstrate how to use the command line options -r, -f, -b and -w. In addition, there are several conversion scripts (for Linux/Unix), with which different common input formats can be converted into the format required by the FP-growth program.

In the file test1.tab transactions are separated by newline characters (that is, each line of the file contains one transaction) and the items of a transaction are separated by spaces. That is, the file test1.tab looks like this:

a b c
a d e
b c d
a b c d
b c
a b d
d e
a b c d
c d e
a b c

As can be seen, there are ten transactions over the item base {a, b, c, d, e}, which contain between two and four items each.

The file test1.tab is in the standard input format and hence it can be processed directly:

fpgrowth test1.tab test1.out

Instead of spaces, tabulators may be used, and it is possible to mix spaces and tabulators. Note, however, that multiple consecutive white space characters (like multiple spaces or a space and a tabulator etc.) are interpreted as a single field separator. The reason is that by default spaces, tabulators and the carriage return character are interpreted as blank characters, which are removed when reading items. Hence only the first white space character after an item is interpreted as a field separator, all following white space characters are interpreted as blanks.

Note also that commas are among the default field separators as well. That is, if the file test1.tab looked like this:

a,b,c
a,d,e
b,c,d
a,b,c,d
b,c
a,b,d
d,e
a,b,c,d
c,d,e
a,b,c

it could still be processed directly with the command stated above. You may also mix spaces, tabulators and commas.

Unfortunately, though, the fact that commas are interpreted as field separators does not necessarily mean that CSV-files (where CSV stands for "comma separated values"), as they can be written by programs like Microsoft Excel, can be processed directly. The reason is that in a CSV-file all lines contain the same number of fields. That is, in CSV-format, the above input file would look like this (file test1.csv in directory fpgrowth/ex):

a,b,c,
a,d,e,
b,c,d,
a,b,c,d
b,c,,
a,b,d,
d,e,,
a,b,c,d
c,d,e,
a,b,c,

Note the single and double commas at the end of most lines, which separate empty fields (as these transactions have fewer items than the longest transaction). While a single comma at the end of a line does not cause any problems and is simply ignored, two or more commas lead to an error message "item expected", because an item may not be an empty string. This can be fixed by declaring the comma a blank character (option -b). That is, the CSV-file can be processed with:

fpgrowth -b, test1.csv test1.out

Note, however, that the characters given with the option -b replace the default blank characters. So if you still need spaces to be interpreted as blanks, they have to be specified as well:

fpgrowth -b" ," test1.csv test1.out

In the file test2.tab the same transactions can be found, but several different field separators are used:

a,b,c
a,d,e
b.c.d
a,b,c,d
b:c
a,b,d
d,e
a,b,c,d
c;d;e
a,b,c

The file test2.tab can be processed by declaring different field separators with the option -f:

fpgrowth -f",.;:" -l test2.tab test2.out

The file test3.tab has basically the same format as the file test1.tab, with the only difference that the last fields of each record states an (integer) transaction weight/multiplicity.

a b c 2
a d e 1
b c d 1
a b c d 2
b c 1
a b d 1
d e 1
c d e 1

This allows us to combine transactions, so that test2.tab has only 8 lines, while test1.tab has 10 lines, because the transactions a b c and a b c d occur twice. In order to instruct the FP-growth program to interpret the last field of each record as such a weight/multiplicity, is has to be invoked with the option -w:

fpgrowth -w test3.tab test3.out

The files test4.tab to test6.tab are in formats that may be common, but which cannot be processed directly with the FP-growth program.

In the file test4.tab each line contains a transaction identifier and an item, separated by a space (not shown because of the large number of lines). This file can be converted (on Linux/Unix systems) into the standard input format with the script tid2set, i.e., with

tid2set test4.tab x.tab

Note that this script sorts the input file (here: test4.tab) w.r.t. the transaction identifier, so that items belonging to the same transaction occupy consecutive lines/records. That is, the input need not already be sorted by transaction identifier, rather the script does this to make sure that the conversion works.

In the file test5.tab the first line states the item names and the following lines contain flags T (true) and F (false) depending on whether the item is contained in the transaction represented by the line or not:

a b c d e
T T T F F
T F F T T
F T T T F
T T T T F
F T T F F
T T F T F
F F F T T
T T T T F
F F T T T
T T T F F

This format can be converted (on Linux/Unix systems) into the standard input format with the script flg2set, i.e., with

flg2set test5.tab x.tab

This script interprets T, t, and 1 as "true", that is, as indicators that the item corresponding to the column is contained in the transaction corresponding to the row, and any other entry as "false" (the item is not contained in the transaction).

In the file test6.tab there is one item per line and transactions are separated by blank lines (not shown here because of the large number of lines). This format can be converted (on Linux/Unix systems) into the standard input format with the script row2set, i.e., with:

row2set test6.tab x.tab

Note that the file test6.tab could be processed directly if the transactions were not separated by a mere empty line (that is, two newline characters following each other), but if the empty line contained a special character, for example %. In this case the file can be processed directly with

fpgrowth -r"%" -f"\n" -b"\n" test6.tab x.tab

The additional scripts tab2set and hdr2set convert tables with column numbers or column names into a format appropriate for the FP-growth program. They are invoked in the same way as all other scripts discussed above, i.e., with

tab2set a.tab b.tab

or

hdr2set a.tab b.tab

where a.tab is the name of the input file and b.tab the name of the output file. The script tab2set replaces each table entry "x" of the input file by "Xi=x", where i is the column number (starting with 1).

The script hdr2set reads the variable names from the first line of the input file and then replaces each table entry "x" by "X=x", where "X" is the variable name that was found in the corresponding column of the first line. These scripts are handy if you want to process tabular data by treating each table row as a transaction.

Note that any input may also be read from standard input and any output may be sent to standard output, simply by specifying a '-' or an empty string "" instead of a filename. For example (on a Linux/Unix system)

cat test1.tab | fpgrowth - -

reads the transactions from standard input (where they are fed by the cat command) and writes the found frequent item sets directly to the terminal. They may be piped to any other program or script, since all other messages of the FP-growth program are written to standard error.

back to the top		top
Format of the Item Selection File

In addition to an input file with the transactions and an output file for the found item sets, an item selection file may be passed to the FP-growth program with the option -R. This file lists a selection of items that are to be included in the search, while any items not listed in this file are to be ignored. It can be seen as a specification of the item base for the search.

The item selection file has to be a (text) file structured by the same field and record separators and blanks as the transactions file. Items may be listed in a single record or in multiple records; it does not matter in which record an item occurs. All that matters is whether an item occurs in the item selection file (then it is included in the search) or not (then it is ignored).


**Output Format
The output format for item sets is fairly flexible. Especially the output of the additional information about item sets (support, additional evaluation) can be formatted freely.

Format of Frequent Item Sets

Each line of the output file contains one item set in the format

A B C [...] <add. info>

where A, B and C are item identifiers, and <add. info> is determined by the additional information output format (option -v). The item separator may be changed with the option -k. For example,

fpgrowth -k, test1.tab test.out

produces output in the format

A,B,C,[...] <add. info>

Each output line may be preceded by a string that is specified with the option -h (record header for output).

The output format for the additional rule information can be any string with the following special format symbols (similar to the style of the special format symbols of the printf function in the programming language C):

%%		a percent sign
%i		number of items (item set size)
%a		absolute item set support
%s		relative item set support as a fraction
%S		relative item set support as a percentage
%e		additional evaluation measure
%E		additional evaluation measure as a percentage
All format specifiers can be extended by an integer number between the percent sign and the defining character, which specifies the number of decimal digits to be printed (expect those that refer to integer numbers, like the number of items and the absolute support, for which such a number of digits is ignored). If no such number is given, (up to) six significant digits are reported.

The default additional information output format is for item sets " (%S)". That is, the relative support of the item set is printed with (up to) six significant digits, enclosed in parentheses. Two spaces separate the additional information from the last item in the set. The default format is automatically changed to " (%a)" if the minimum support (option -s) is given as a negative number (absolute support), so that the output is consistent with the support threshold.

Format of a Pattern Spectrum

A pattern spectrum collects the number of found frequent item sets sub-divided by the size and the support of the item sets. Pattern spectra (together with surrogate data/randomization methods) can be useful to determine the statistical significance of found frequent item sets. Details can be found in the papers [Picado-Muino et al. 2013] and [Torre et al. 2013].

FP-growth implementation can be instructed to collect and write a pattern spectrum with the option -P, which takes the name of the file to which the patterns spectrum is to be written as a parameter.

A pattern spectrum is written as a list of (size, support, count) triplets. The output file is a simple text file that contains one triplet per line, with the three numbers separated by spaces. For example, for the input file test1.tab (see this section) the pattern spectrum is (with default option settings):

1 3 1
1 6 1
1 7 3
2 1 2
2 3 1
2 4 4
2 5 1
2 6 1
3 1 2
3 2 1
3 3 2
3 4 1
4 2 1

The first column contains the different sizes of item sets, the second column the difference support values, and the third column the number of item sets found for the corresponding (size, support) combination. For example, the sixth row indicates that there are four frequent item sets with two items and support 4. Note that in a pattern spectrum the support is always given as absolute support, that is, as a number of transactions.

####Author/Student and Licence

DELVERI MUNANG, Department of Computer Engineering, University of Buea.
This Code is developed in part from Christian Borgelt's work on Frequent set mining and Code distributed under the MIT Licence.
An Implementation of the FP-growth Algorithm
Christian Borgelt
Workshop Open Source Data Mining Software (OSDM'05, Chicago, IL), 1-5.
ACM Press, New York, NY, USA 2005.

