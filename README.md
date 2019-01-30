# NYU Tandon's [OSIRIS Lab](http://osiris.cyber.nyu.edu/)'s [Hack Night](https://www.osiris.cyber.nyu.edu/hack-night)
Developed from both the materials of the NYU Tandon's Introduction to Offensive Security and old Penetration Testing and Vulnerability Analysis course, Hack Night is a sobering introduction to offensive security. A lot of complex technical content is covered very quickly as students are introduced to a wide variety of complex and immersive topics over thirteen weeks.

Hack Night culminates in a practical application of the skills and techniques taught, students complete a research project inspired by one of the lectures or exercise materials. By the end of the course, each student is expected to have a good understanding of all topics and a mastery of at least one topic.

*Due to the involved nature of this course, we recommend students attend Hack Night in person.*

## Logistics
If you have any questions, or would like to attend a Hack Night session, you can contact or eboard@osiris.cyber.nyu.edu or you can [file a ticket](https://github.com/osirislab/Hack-Night/issues) in Github.

Sign up for the [Cyber Security Club mailing list](https://www.osiris.cyber.nyu.edu/newsletter) to recieve weekly e-mails about seminars and training sessions brought to you by the [OSIRIS Lab](http://osiris.cyber.nyu.edu/).

Hack Night is run every Thursday during the regular semester at 7 PM in RH 217, check [our calendar for updates](https://www.osiris.cyber.nyu.edu/calendar).

OSIRIS Lab, RH 219 
Six MetroTech Center  
Brooklyn, NY 11201


## Week 0: Background
In order to get the most out of Hack Night, you should be familiar with some basic security concepts.

### Lecture Materials
1. [PicoCTF Resources](https://picoctf.com/learn)

### Resources
#### Application Security
1. [OWASP Secure Coding Principles](https://www.owasp.org/index.php/Secure_Coding_Principles)

#### Web Security
1. [OWASP Top 10](https://www.owasp.org/index.php/Category:OWASP_Top_Ten_Project)


## Week 1: Introduction
This is an introduction session to the Hack Night curriculum, this session tries to give an overview of what rest of Hack Night sessions is to be followed. More importantly, it also gives the
ethics necessary to keep in mind when you learn something as powerful as you're going to do now. Next, we will cover various types of disclosure that hackers have followed since
its inception.

Before diving into the Hack Night semester, we recommend you take a look at the resources below and become familiar with some of the material.
This session will cover Code Auditing. Code Auditing an application is the process of analyzing application code (in source or binary form) to uncover vulnerabilities that attackers
might exploit. By going through this process, you can identify and close security holes that would otherwise put sensitive data and business resources at unnecessary risk.
Topics that will be covered are Identifying Architectural, Implementation and Operational vulnerabilities.


### Lecture Materials
1. [Slides](Intro/Week1.pdf)
2. [The Art of Software Security Assessment](http://www.amazon.com/Art-Software-Security-Assessment-Vulnerabilities/dp/0321444426/ref=sr_1_1?s=books&ie=UTF8&qid=1367449909&sr=1-1&keywords=the+art+of+software+security+assessment)
3. [Integer Overflows](http://en.wikipedia.org/wiki/Integer_overflow)
4. [Catching Integer Overflows](http://www.fefe.de/intof.html)
5. [The Fortify Taxonomy of Software Security Flaws](http://www.fortify.com/vulncat/)

### Resources
1. [IRC: #hacknight on isis.poly.edu port 6697 (ssl only)](http://chat.mibbit.com/?server=isis.poly.edu%3A%2B6697&channel=%23hacknight)
2. [OSIRIS Lab Blog](https://blog.osiris.cyber.nyu.edu/)
3. [OSIRIS Lab Github](https://github.com/osirislab/)
4. [Project Ideas](https://github.com/osirislab/Project-Ideas/issues)
5. [CTF 101](https://ctf101.org/)
6. [Mailing List](https://www.osiris.cyber.nyu.edu/newsletter)
7. [OSIRIS Lab Calendar](https://www.osiris.cyber.nyu.edu/calendar)

### Tools
1. [Source Navigator](http://sourcenav.sourceforge.net/)
2. [Scitools Understand](http://www.scitools.com/)
3. [List of tools for static code analysis](http://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis)

### Workshop
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)


## Weeks 2 and 3: Server-side Web Security
This session will cover web hacking. This session is about getting familiarity with various vulnerabilities commonly found in web applications. You will be able to identify and exploit web application vulnerabilities. 
Topics to be covered are:
* SQL Injection
* File inclusion
* Directory Traversal
* Object deserialization
* External Entities (XXE) Injection
* CRLF Injection
* Server-Side Request Forgery
* WAFs and filter bypasses

### Lecture Materials
1. [Slides](Web/ServerSide.pdf)

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [The Tangled Web](http://nostarch.com/tangledweb.htm)
2. [OWASP Top 10](https://www.owasp.org/index.php/Top_10)
3. [OWASP Top 10 Tools and Tactics](http://resources.infosecinstitute.com/owasp-top-10-tools-and-tactics/)

### Tools
1. [Burp suite](https://portswigger.net/)


## Week 4: Client-Side Web Security
This session will cover client-side web hacking. This session is about familiarity with various client-side applications in web applications. We will also look at exploitation mitigations that your current browser implements. Topics include XSS, CSRF, Same-Origin Policy, XSS-Protection, and Content-Security-Policy.

### Lecture Materials
1. [Slides](Web/ClientSide.pdf)

### Workshop Materials
1. [Google XSS game](https://xss-game.appspot.com/)
2. [Hacknight CSP Game]()

### Resources
2. [The Tangled Web](http://nostarch.com/tangledweb.htm)
3. [OWASP Top 10](https://www.owasp.org/index.php/Top_10)
4. [OWASP Top 10 Tools and Tactics](http://resources.infosecinstitute.com/owasp-top-10-tools-and-tactics/)
5. [OWASP XSS Filter Evasion Cheat Sheet](https://www.owasp.org/index.php/XSS_Filter_Evasion_Cheat_Sheet)


## Week 5: Reverse Engineering, Part 1
This session is about Reverse Engineering. Most of the software we use everyday is closed source. You don't have the liberty to look at the source code, at this point we need to analyze the available compiled binary. Reversing a binary is no easy task but can be done with the proper methodology and the right tools.

This first week will be a primer on x86 assembly and low level programming.

### Lecture Materials
1. [Slides]()

### Workshop Materials
In this section we will go through the basic idea of a binary and how your source code is converted into an executable form. We will then look at the assembly language used by executable programs and develop our own low level programs. We will write simple assembly language programs and teach the basic skills needed to understand more complex assembly language uses.

This is going to be a workshop were we will write programs at assembly level. Once, we get familiar to basic x86 instructions we will switch to analyzing a real application and try to get high level understanding of what the application is doing. The goal would be to get familiar with calling conventions, stack and stack frames.

1. [Assembly Programming Exercises](https://github.com/blankwall/asm_prog_ex)

### Resources
1. [Binary Ninja Demo](https://binary.ninja/demo/)
2. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
3. [x86 Win32 Reverse Engineering Cheatsheet](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf?raw=true)
4. [IDA Pro Shortcuts](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/IDA_Pro_Shortcuts.pdf?raw=true)
5. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
6. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
7. [nasm](http://www.nasm.us/)
8. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)


## Week 6: Reverse Engineering, Part 2
We will present you with an application which has no source code. Your job is to understand what the application is doing and figure out any loopholes present in that application. You'll use static analysis tools like IDA to analyze the binary and get a complete understanding of the application.

### Lecture Videos
1. [Slides]()

### Workshop Materials
1. [CMU Bomb Lab](http://csapp.cs.cmu.edu/public/1e/bomb.tar) (Linux/IA32 binary)

### Resources
1. [Binary Ninja Demo](https://binary.ninja/demo/)
2. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
3. [x86 Win32 Reverse Engineering Cheatsheet](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf?raw=true)
4. [IDA Pro Shortcuts](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/IDA_Pro_Shortcuts.pdf?raw=true)
5. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
6. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
7. [nasm](http://www.nasm.us/)
8. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)


## Week 7: Reverse Engineering, Part 3
In this session we will cover [Introductory Intel x86: Architecture, Assembly, Applications, and Alliteration by Xeno Kovah](http://www.opensecuritytraining.info/IntroX86.html) from [OpenSecurityTraining](http://www.opensecuritytraining.info/Welcome.html). Intel processors have been a major force in personal computing for more than 30 years. An understanding of low level computing mechanisms used in Intel chips as taught in this course serves as a foundation upon which to better understand other hardware, as well as many technical specialties such as reverse engineering, compiler design, operating system design, code optimization, and vulnerability exploitation. 50% of the time will be spent learning Windows/Linux tools and analysis of "simple" programs.

### Lecture Materials
1. [Introductory Intel x86 Lectures](http://www.youtube.com/playlist?list=PL038BE01D3BAEFDB0)

### Workshop Materials
1. [CMU Bomb Lab](http://csapp.cs.cmu.edu/public/1e/bomb.tar) (Linux/IA32 binary)
2. [Pwndbg GDB Plugin](https://github.com/pwndbg/pwndbg)

### Resources
1. [Binary Ninja Demo](https://binary.ninja/demo/)
2. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
3. [x86 Win32 Reverse Engineering Cheatsheet](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf?raw=true)
4. [IDA Pro Shortcuts](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/IDA_Pro_Shortcuts.pdf?raw=true)
5. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
6. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
7. [nasm](http://www.nasm.us/)
8. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)
9. [GDB Commands Cheatsheet](http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)

## Week 8: Reverse Engineering, Part 4
Last week you dynamically debugged and reverse engineered a program that used a basic anti-reverse engineering technique. We will be going over some anti-reverse engineering protections. 

### Lecture Materials 
1. [Slides]()

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [Binary Ninja Demo](https://binary.ninja/demo/)
2. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
3. [x86 Win32 Reverse Engineering Cheatsheet](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf?raw=true)
4. [IDA Pro Shortcuts](https://github.com/isislab/Hack-Night/blob/master/2014-Fall/references/IDA_Pro_Shortcuts.pdf?raw=true)
5. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
6. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
7. [nasm](http://www.nasm.us/)
8. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)
9. [GDB Commands Cheatsheet](http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)


## Week 9: Memory Corruption, Part 1
In this week's session, we will go over some advanced concepts related to computer security. We will go over various memory errors that an application can cause often leading to catastrophic results. Topics that will be covered are various memory errors like buffer overflows, uninitialized variables, use after free etc. and how we can use them to take control of an application. 
### Lecture Materials
1. [Slides]()

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [Smashing the Stack for Fun and Profit](http://www-inst.eecs.berkeley.edu/~cs161/fa08/papers/stack_smashing.pdf)
2. [Vagrant](https://www.vagrantup.com/)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [pwndbg](https://github.com/pwndbg/pwndbg)
5. [pwntools](https://github.com/Gallopsled/pwntools)


## Week 10: Memory Corruption, Part 2
This week, We will look at exploitation mitigation that your current OS implements, it's not 1988 anymore. We will look at some techniques used to bypass modern mitigations. We will also go over useful tools and techniques for writing exploits.

### Lecture Materials
1. [Slides]()

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [Smashing the Stack for Fun and Profit](http://www-inst.eecs.berkeley.edu/~cs161/fa08/papers/stack_smashing.pdf)
2. [Vagrant](https://www.vagrantup.com/)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [pwndbg](https://github.com/pwndbg/pwndbg)
5. [pwntools](https://github.com/Gallopsled/pwntools)


## Week 11: Heap Exploitation, Part 1
In this week, we will cover the fundamentals of the Heap. We will primarily focus on the glibc implementation of the heap, but these techniques will apply to other implementations as well. 
We will go over the basic idea of how Glibc malloc behaves and is implemented, and then go into the following introductory heap exploitation techniques:
* Use after free
* Heap spraying
* Heap overflows
* Unlink
* Overlapping chunks
* Nullbyte poison

### Lecture Materials
1. [Slides]()

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [Smashing the Stack for Fun and Profit](http://www-inst.eecs.berkeley.edu/~cs161/fa08/papers/stack_smashing.pdf)
2. [Vagrant](https://www.vagrantup.com/)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [pwndbg](https://github.com/pwndbg/pwndbg)
5. [pwntools](https://github.com/Gallopsled/pwntools)
6. [How2heap](https://github.com/shellphish/how2heap)

### Lecture Material
1. [Post Exploitation](http://vimeo.com/33344191)

## Week 11: Heap Exploitation, Part 1
In this week, we will cover the fundamentals of the Heap. We will primarily focus on the glibc implementation of the heap, but these techniques will apply to other implementations as well. 
We will go over the basic idea of how Glibc malloc behaves and is implemented, and then go into the following introductory heap exploitation techniques:
* Use after free
* Heap spraying
* Heap overflows
* Unlink
* Overlapping chunks
* Nullbyte poison

### Lecture Materials
1. [Slides]()

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [How2heap](https://github.com/shellphish/how2heap)
2. [Vagrant](https://www.vagrantup.com/)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [pwndbg](https://github.com/pwndbg/pwndbg)
5. [pwntools](https://github.com/Gallopsled/pwntools)


## Week 12: Heap Exploitation, Part 2
In this week, we will cover the advanced heap exploitation techniques.

### Lecture Materials
1. [Slides]()

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [How2heap](https://github.com/shellphish/how2heap)
2. [Vagrant](https://www.vagrantup.com/)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [pwndbg](https://github.com/pwndbg/pwndbg)
5. [pwntools](https://github.com/Gallopsled/pwntools)


## Week 13: Kernel Exploitation
In thi sweek, we will cover the fundamentals of operating systems and how we can use our memory corruption skills for operating systems. The techniques and fundamentals will be the same, but there will be slight differences in the ecosystem, goals, and functions called for kernel exploitation.

### Lecture Materials
1. [Slides]()

### Workshop Materials
1. [OSIRIS Wargames](wargames.osiris.cyber.nyu.edu)

### Resources
1. [RPISEC's Modern Binary Exploitation](http://security.cs.rpi.edu/courses/binexp-spring2015/)
2. [Vagrant](https://www.vagrantup.com/)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [pwndbg](https://github.com/pwndbg/pwndbg)
5. [pwntools](https://github.com/Gallopsled/pwntools)

## Conclusion
Hack Night is designed to culminate in each student developing some kind of deliverable related to computer security, the goal being that everyone leaves the program with more knowledge about security.
