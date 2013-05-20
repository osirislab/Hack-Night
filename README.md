Hack-Night
==========

## Week 1: Introduction
This is an introduction session to the Hack Night curriculum, this session tries to give an overview of what rest HN sessions is to be followed. More importantly, it also gives the
ethics necessary to keep in mind when you learn something as powerful as your going to do now. Next, we will cover various types of disclosure that hackers have followed since
its inception.

### Lecture Materials
1. [Trends in Vulnerability Disclosure](http://vimeo.com/48914102)
2. [Introduction to Vulnerability Analysis](http://vimeo.com/49284329)


## Week 2: Code Auditing
This session will cover Code Auditing. Code Auditing an application is the process of analyzing application code (in source or binary form) to uncover vulnerabilities that attackers
might exploit. By going through this process, you can identify and close security holes that would otherwise put sensitive data and business resources at unnecessary risk.
Topics that will be covered are Identifying Architectural, Implementation and Operational vulnerabilities.

### Lecture Materials
1. [Design & Operational Reviews](http://vimeo.com/29082852/) [slides](http://pentest.cryptocity.net/files/code_analysis/design_review_fall2011.pdf)
2. [Code Auditing 101](http://vimeo.com/30001189/) [slides](http://pentest.cryptocity.net/files/code_analysis/code_audits_1_fall2011.pdf)
3. [Code Auditing 102](http://vimeo.com/29702192/) [slides](http://pentest.cryptocity.net/files/code_analysis/code_audits_2_fall2011.pdf)


### Resources
1. [The art of software security assessment](http://www.amazon.com/Art-Software-Security-Assessment-Vulnerabilities/dp/0321444426/ref=sr_1_1?s=books&ie=UTF8&qid=1367449909&sr=1-1&keywords=the+art+of+software+security+assessment) Chapters: 1, 2, 3, 6.
2. [Integer Overflows](http://en.wikipedia.org/wiki/Integer_overflow) and [Catching Integer Overflows](http://www.fefe.de/intof.html)
3. [The Fortify Taxonomy of Software Security Flaws](http://www.fortify.com/vulncat/)
4. [List of tools for static code analysis](http://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis)


## Week 3: Code Auditing Workshop
This is a workshop session, we will present you with some applications that are intentionally vulnerable. Your job is to audit the source code and find vulnerabilities in them. Test
the skills that you have learned last week to efficiently go over the process of auditing applications.

### Workshop Materials
1. [Client Request Access Protocol](http://pentest.cryptocity.net/files/code_analysis/designdoc-fall2010.pdf)
We believe this protocol to be severely flawed and require your assistance in identifying vulnerabilities in it. Your objective is to identify and informally describe as many of these issues that you can.
2. [News Paper](http://pentest.cryptocity.net/files/code_analysis/fall2011_hw2.c)  [Simple Usage] (http://pentest.cryptocity.net/files/code_analysis/fall2011_install.sh)
This network service simulates a text-based terminal application. The general purpose of the application is to act as a "news server" or text file service. These are two types of users: regular and administrator. Administrators can add users and execute back-end system commands. Users can view and contribute articles (aka text files). Assume the application runs on Linux and is compiled with gcc.
