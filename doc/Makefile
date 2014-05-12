default:
	#pandoc -s report.txt -o report.tex
	pandoc -V documentclass=acm_proc_article-sp report.txt -o report.pdf --bibliography=biblio.bib
	#pandoc report.txt -o report.pdf 
	#pandoc -v documentclass=sig-alternate report.txt -o report.pdf 
	open report.pdf

