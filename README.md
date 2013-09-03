# NYU Poly [ISIS Lab](http://www.isis.poly.edu/)'s [Hack Night](http://www.isis.poly.edu/hack-night)
Developed from the materials of NYU Poly's [old Penetration Testing and Vulnerability Analysis course](http://pentest.cryptocity.net/), Hack Night is a sobering introduction to offensive security. A lot of complex technical content is covered very quickly as students are introduced to a wide variety of complex and immersive topics over thirteen weeks.

Hack Night culminates in a practical application of the skills and techniques taught, students complete a research project inspired by one of the lectures or exercise materials. By the end of the course, each student is expected to have a good understanding of all topics and a mastery of at least one topic.

*Due to the involved nature of this course, we recommend students attend Hack Night in person.*

## Logistics
If you have any questions, or would like to attend a Hack Night session, you can contact Evan Jensen or Marc Budofsky at HackNight@isis.poly.edu or you can [file a ticket](https://github.com/isislab/Hack-Night/issues) in Github.

Sign up for the [Cyber Security Club mailing list](https://isis.poly.edu/mailman/listinfo/csc) to recieve weekly e-mails about seminars and training sessions brought to you by the [ISIS Lab](http://www.isis.poly.edu/).

Hack Night is run every Wednesday during the regular semester at 6 PM in RH 219, check [our calendar for updates](http://www.isis.poly.edu/calendar).

ISIS Lab, RH 219  
Six MetroTech Center  
Brooklyn, NY 11201


## Week 0: Background
In order to get the most out of Hack Night, you should be familiar with some basic security concepts.

### Lecture Materials
1. [PicoCTF Resources](https://picoctf.com/learn)

### Resources
#### General
1. [Sun Certified Security Administrator for Solaris 9 & 10 Study Guide Chapter 1](http://www.mhprofessional.com/downloads/products/0072254238/0072254238_ch01.pdf)

#### Application Security
1. [OWASP Secure Coding Principles](https://www.owasp.org/index.php/Secure_Coding_Principles)

#### Exploitation
1. [Windows ISV Software Security Defenses](http://msdn.microsoft.com/en-us/library/bb430720.aspx)

#### Mobile Security
1. [OWASP Top 10](https://www.owasp.org/index.php/Projects/OWASP_Mobile_Security_Project_-_Top_Ten_Mobile_Risks)

#### Network Security
1. [Common Types of Network Attacks](http://technet.microsoft.com/en-us/library/cc959354.aspx)

#### Reverse Engineering
1. [University of Washington's The Hardware/Software Interface](https://class.coursera.org/hwswinterface-001/class)  *Currently Unavailable to New Students*
2. [University of London's Malicious Software and its Underground Economy: Two Sides to Every Story](https://class.coursera.org/malsoftware-001/class)

#### Web Security
1. [OWASP Top 10](https://www.owasp.org/index.php/Category:OWASP_Top_Ten_Project)


## Week 1: Introduction
This is an introduction session to the Hack Night curriculum, this session tries to give an overview of what rest of Hack Night sessions is to be followed. More importantly, it also gives the
ethics necessary to keep in mind when you learn something as powerful as your going to do now. Next, we will cover various types of disclosure that hackers have followed since
its inception.

Before diving into the Hack Night semester, we recommend you take a look at the resources below and become familiar with some of the material.

### Lecture Materials
1. [Trends in Vulnerability Disclosure](http://vimeo.com/48914102)
2. [Intrusion via Web Application Flaws](http://vimeo.com/14983596)
3. [Intrusion via Client-Side Exploitation](http://vimeo.com/14983828)

### Resources
1. [IRC: #hacknight on isis.poly.edu port 6697 (ssl only)](http://chat.mibbit.com/?server=isis.poly.edu%3A%2B6697&channel=%23hacknight)
2. [ISIS Lab Blog](https://isisblogs.poly.edu/)
3. [ISIS Lab Github](https://github.com/isislab/)
4. [Project Ideas](https://github.com/isislab/Project-Ideas/issues)
5. [Resources Wiki](https://github.com/isislab/Project-Ideas/wiki)
6. [CyFor](http://cyfor.isis.poly.edu/)
7. [Cyber Security Club Mailing List](https://isis.poly.edu/mailman/listinfo/csc)
8. [ISIS Lab Calendar](http://www.isis.poly.edu/calendar)


## Week 2: Source Code Auditing, Part 1
This session will cover Code Auditing. Code Auditing an application is the process of analyzing application code (in source or binary form) to uncover vulnerabilities that attackers
might exploit. By going through this process, you can identify and close security holes that would otherwise put sensitive data and business resources at unnecessary risk.
Topics that will be covered are Identifying Architectural, Implementation and Operational vulnerabilities.

### Lecture Materials
1. [Design & Operational Reviews](http://vimeo.com/29082852/) [[slides](http://pentest.cryptocity.net/files/code_analysis/design_review_fall2011.pdf)]
2. [Code Auditing 101](http://vimeo.com/30001189/) [[slides](http://pentest.cryptocity.net/files/code_analysis/code_audits_1_fall2011.pdf)]

### Workshop Materials
1. [Client Request Access Protocol](http://pentest.cryptocity.net/files/code_analysis/designdoc-fall2010.pdf)
We believe this protocol to be severely flawed and require your assistance in identifying vulnerabilities in it. Your objective is to identify and informally describe as many of these issues that you can.

### Resources
1. [Source Code Analysis](https://github.com/isislab/Project-Ideas/wiki/Source-Code-Analysis)
2. [Application Security](https://github.com/isislab/Project-Ideas/wiki/Application-Security)
3. [The Art of Software Security Assessment](http://www.amazon.com/Art-Software-Security-Assessment-Vulnerabilities/dp/0321444426/ref=sr_1_1?s=books&ie=UTF8&qid=1367449909&sr=1-1&keywords=the+art+of+software+security+assessment)
4. [Integer Overflows](http://en.wikipedia.org/wiki/Integer_overflow)
5. [Catching Integer Overflows](http://www.fefe.de/intof.html)
6. [The Fortify Taxonomy of Software Security Flaws](http://www.fortify.com/vulncat/)


## Week 3: Source Code Auditing, Part 2
This week we will continue with the final video on Code Auditing, and provide you with 2 more applications that are intentionally vulnerable. Your job is to audit the source code and find vulnerabilities in them. Test
the skills that you have learned last week to efficiently go over the process of auditing applications.

### Lecture Materials
1. [Code Auditing 102](http://vimeo.com/29702192/) [[slides](http://pentest.cryptocity.net/files/code_analysis/code_audits_2_fall2011.pdf)]

### Workshop Materials
1. [News Paper](http://pentest.cryptocity.net/files/code_analysis/fall2011_hw2.c)  [Simple Usage](http://pentest.cryptocity.net/files/code_analysis/fall2011_install.sh)
This network service simulates a text-based terminal application. The general purpose of the application is to act as a "news server" or text file service. These are two types of users: regular and administrator. Administrators can add users and execute back-end system commands. Users can view and contribute articles (aka text files). Assume the application runs on Linux and is compiled with gcc.
2. [Siberia Crimeware Pack](http://pentest.cryptocity.net/files/code_analysis/siberia.zip) (Password: infected)
The Siberia kit contains live exploit code and will likely set off AV, however none of the exploit code is in a state where it would be harmful to your computer. In addition to all of the vulnerabilites have been patched years ago, the exploits in Siberia need to be interpreted by PHP and read by your browser for them to have any effect. You can safely disable or create exceptions in your AV for this exercise or place the Siberia files inside a VM.

### Resources
1. [Source Code Analysis](https://github.com/isislab/Project-Ideas/wiki/Source-Code-Analysis)
2. [Application Security](https://github.com/isislab/Project-Ideas/wiki/Application-Security)
3. [The Art of Software Security Assessment](http://www.amazon.com/Art-Software-Security-Assessment-Vulnerabilities/dp/0321444426/ref=sr_1_1?s=books&ie=UTF8&qid=1367449909&sr=1-1&keywords=the+art+of+software+security+assessment)
4. [Integer Overflows](http://en.wikipedia.org/wiki/Integer_overflow)
5. [Catching Integer Overflows](http://www.fefe.de/intof.html)
6. [The Fortify Taxonomy of Software Security Flaws](http://www.fortify.com/vulncat/)

### Tools
1. [Source Navigator](http://sourcenav.sourceforge.net/)
2. [Scitools Understand](http://www.scitools.com/)
3. [List of tools for static code analysis](http://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis)


## Week 4: Web Security, Part 1
This session will cover web hacking. This session is about getting familiarity with various vulnerabilities commonly found in web applications. You will be able to identify and exploit web application vulnerabilities. Topics to be covered are web application primer, Vuln. commonly found in web apps. (OWASP Top 10) and Basic web testing methodologies.

### Lecture Materials
1. [Web Hacking 101](http://vimeo.com/32509769) [[slides](http://pentest.cryptocity.net/files/web/2011/Web%20Hacking%20Day%201%20-%202011.pdf)]

### Workshop Materials
1. [Google Gruyere](http://google-gruyere.appspot.com/)


### Resources
1. [Web Security](https://github.com/isislab/Project-Ideas/wiki/Web-Security)
2. [The Tangled Web](http://nostarch.com/tangledweb.htm)
3. [OWASP Top 10](https://www.owasp.org/index.php/Top_10)
4. [OWASP Top 10 Tools and Tactics](http://resources.infosecinstitute.com/owasp-top-10-tools-and-tactics/)


## Week 5: Web Security, Part 2
In this session, we will continue with the second video on Web Hacking.  We will then be using some more intentionally vulnerable web applications to identify and analyze the top ten vulnerabilities commonly found in the web applications  You will be going through the steps of busticating a real site and throwing a fire sale using freely available tools.

### Lecture Materials
1. [Web Hacking 102](http://vimeo.com/32550671) [[slides](http://pentest.cryptocity.net/files/web/2011/Web%20Hacking%20Day%202%20-%202011.pdf)]

### Workshop Materials
1. [OWASP WebGoat](https://www.owasp.org/index.php/Category:OWASP_WebGoat_Project)
2. [Damn Vulnerable Web Application](http://www.dvwa.co.uk/)


### Resources
1. [Web Security](https://github.com/isislab/Project-Ideas/wiki/Web-Security)
2. [The Tangled Web](http://nostarch.com/tangledweb.htm)
3. [OWASP Top 10](https://www.owasp.org/index.php/Top_10)
4. [OWASP Top 10 Tools and Tactics](http://resources.infosecinstitute.com/owasp-top-10-tools-and-tactics/)


## Week 6: Reverse Engineering, Part 1
This session is about Reverse Engineering.  Most of the software we use everyday is closed source. You don't have the liberty to look at the source code, at this point we need to analyze the available compiled binary. Reversing a binary is no easy task but can be done with the proper methodology and the right tools. This is exactly what two of world's best reverse engineers are going to teach you.

### Lecture Videos
1. [Reverse Engineering 101](http://vimeo.com/6764570)
2. [Reverse Engineering 102](http://vimeo.com/30076325)  [[slides](http://pentest.cryptocity.net/files/reversing/sotirov-re-fall2011.pdf)]

### Workshop Materials
1. [Challenge Application](http://128.238.66.181/easy32)

### Resources
1. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
2. [Application Security](https://github.com/isislab/Project-Ideas/wiki/Application-Security)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [x86 Win32 Reverse Engineering Cheatsheet](http://pentest.cryptocity.net/files/reversing/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf)
5. [IDA Pro Shortcuts](http://pentest.cryptocity.net/files/reversing/IDA_Pro_Shortcuts.pdf)
6. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
7. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
8. [nasm](http://www.nasm.us/)
9. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)


## Week 7: Reverse Engineering, Part 2
Picking up from previous session, we will watch the last video on Reverse Engineering, and present you with an application which has no source code. Your job is to understand what the application is doing and figure out any loopholes present in that application. You'll use static analysis tools like IDA and varied dynamic analysis to analyze the binary and get a complete understanding of the application.

### Lecture Videos
1. [Dynamic Reverse Engineering](http://vimeo.com/30594548)  [[slides](http://pentest.cryptocity.net/files/reversing/2011/dynamic_reversing_2011.pdf)]

### Workshop Materials
1. [demo.exe](http://pentest.cryptocity.net/files/exploitation/demo.zip) (Password: infected)

### Resources
1. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
2. [Application Security](https://github.com/isislab/Project-Ideas/wiki/Application-Security)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [x86 Win32 Reverse Engineering Cheatsheet](http://pentest.cryptocity.net/files/reversing/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf)
5. [IDA Pro Shortcuts](http://pentest.cryptocity.net/files/reversing/IDA_Pro_Shortcuts.pdf)
6. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
7. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
8. [nasm](http://www.nasm.us/)
9. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)


## Week 8: Reverse Engineering, Part 3
In this session we will cover [Introductory Intel x86: Architecture, Assembly, Applications, and Alliteration by Xeno Kovah](http://www.opensecuritytraining.info/IntroX86.html) from [OpenSecurityTraining](http://www.opensecuritytraining.info/Welcome.html). Intel processors have been a major force in personal computing for more than 30 years. An understanding of low level computing mechanisms used in Intel chips as taught in this course serves as a foundation upon which to better understand other hardware, as well as many technical specialties such as reverse engineering, compiler design, operating system design, code optimization, and vulnerability exploitation. 50% of the time will be spent learning Windows/Linux tools and analysis of "simple" programs.

### Lecture Materials
1. [Introductory Intel x86 Lectures](http://www.youtube.com/playlist?list=PL038BE01D3BAEFDB0)

### Workshop Materials
1. [CMU Bomb Lab](http://csapp.cs.cmu.edu/public/1e/bomb.tar) (Linux/IA32 binary)

### Resources
1. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
2. [Application Security](https://github.com/isislab/Project-Ideas/wiki/Application-Security)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [x86 Win32 Reverse Engineering Cheatsheet](http://pentest.cryptocity.net/files/reversing/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf)
5. [IDA Pro Shortcuts](http://pentest.cryptocity.net/files/reversing/IDA_Pro_Shortcuts.pdf)
6. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
7. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
8. [nasm](http://www.nasm.us/)
9. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)


## Week 9: Reverse Engineering, Part 4
Picking up from the last week's session, we will continue to explore the world of x86. This is going to be a workshop were we will write programs at assembly level. Once, we get familiar to basic x86 instructions we will switch to analyzing a real application and try to get high level understanding of what the application is doing. The goal would be to get familiar with calling conventions, stack and stack frames.

### Lecture Materials
1. [Introductory Intel x86 Lectures](http://www.youtube.com/playlist?list=PL038BE01D3BAEFDB0)

### Workshop Materials
1. [Write readFile.c in x86 by hand](https://github.com/isislab/Hack-Night/tree/master/2013-Fall/week9)

### Resources
1. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
2. [Application Security](https://github.com/isislab/Project-Ideas/wiki/Application-Security)
3. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
4. [x86 Win32 Reverse Engineering Cheatsheet](http://pentest.cryptocity.net/files/reversing/X86_Win32_Reverse_Engineering_Cheat_Sheet.pdf)
5. [IDA Pro Shortcuts](http://pentest.cryptocity.net/files/reversing/IDA_Pro_Shortcuts.pdf)
6. [All Materials for Introductory Intel x86](http://www.opensecuritytraining.info/IntroX86_files/IntroX86_all_materials_with_pdf_1.zip)
7. [Reverse Engineering](https://github.com/isislab/Project-Ideas/wiki/Reverse-Engineering)
8. [nasm](http://www.nasm.us/)
9. [x86 Intel Manuals](http://www.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)


## Week 10: Exploitation, Part 1
In this week's session, we will go over some advanced concepts related to computer security. Dino Dai Zovi will go over various memory errors that an application can cause often leading to catastrophic results. Topics that will be covered are various memory errors like buffer overflows, uninitialized variables, use after free etc. and how we can use them to take control of an application. We will also look at exploitation mitigation that your current OS implements, it's not 1988 anymore. Finally, we will look at some techniques used to bypass modern mitigations.

### Lecture Materials
1. [Memory Corruption 101](http://vimeo.com/31348274) [[slides](http://pentest.cryptocity.net/files/exploitation/2011/memory_corruption_101.pdf)]

### Workshop Materials
1. [Vulnerable Application](https://github.com/isislab/Hack-Night/tree/master/2013-Fall/week10)

### Resources
1. [Exploitation](https://github.com/isislab/Project-Ideas/wiki/Exploitation)
2. [VMWare Player](http://www.vmware.com/download/player/download.html)
3. [Linux Machine](http://www.ubuntu.com/download/desktop) (preferably, Ubuntu)
4. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
5. [Windbg](http://msdn.microsoft.com/en-us/library/windows/hardware/gg463009.aspx)


## Week 11: Exploitation, Part 2
Picking up from the last session, we will finish watching Dino Dai Zovi's lecture and do a live exploitation of a vulnerable program. We will go through all the steps that Dino explained in his lecture to write a control flow hijacking exploit and take over the program. Once we are done with 1990's style exploitation, we will re-compile the program with modern mitigation technologies and look at various techniques used to bypass these mitigation's.

### Lecture Materials
1. [Memory Corruption 101](http://vimeo.com/31348274) [[slides](http://pentest.cryptocity.net/files/exploitation/2011/memory_corruption_101.pdf)]

### Workshop Materials
1. [demo.exe](http://pentest.cryptocity.net/files/exploitation/demo.zip) (Password: infected)

### Resources
1. [Exploitation](https://github.com/isislab/Project-Ideas/wiki/Exploitation)
2. [VMWare Player](http://www.vmware.com/download/player/download.html)
3. [Linux Machine](http://www.ubuntu.com/download/desktop) (preferably, Ubuntu)
4. [IDA Demo](https://www.hex-rays.com/products/ida/support/download_demo.shtml)
5. [Windbg](http://msdn.microsoft.com/en-us/library/windows/hardware/gg463009.aspx)

### More Challenges
1. [Gera's Insecure Programming by Example](http://community.corest.com/~gera/InsecureProgramming/)
2. [Exploit-Exercises](http://exploit-exercises.com/)


## Week 12: Post-Exploitation
In this week, we will cover post-exploitation. Post-exploitation is the stage in the intrusion kill chain wherein the attacker uses persistence techniques after the victim's system is compromised to maintain his/her presence on the machine. In addition the attacker also wants his presence to be hidden, this includes evading antivirus software, covering his/her tracks, etc. We will look at various techniques used by attackers to achieve the aforementioned goals.

### Lecture Material
1. [Post Exploitation](http://vimeo.com/33344191)

### Workshop Material
As shown in the lecture video, setup two VM’s. One VM will have metasploit running, backtrack is preferred and the other machine will be a Windows box. Preferred, win xp professional or win 7 professional.
Use the psexec module available in metasploit to gain access to the Windows box. Once, you have a meterpreter session available, apply different techniques demonstrated in the lecture like getting the password hash of Administrator, so that you can re-login as Administrator which gives you elevated privileges.

Having a meterpreter session open isn’t necessarily good enough. For instance, run cmd.exe in windows box; get back to your meterpreter session and find the pid of cmd.exe using “ps” command. Once you are able to figure out the pid, use the migrate command to switch to that process. Now, close the command prompt in the windows box. Do you still have the session open? What do you think a stable process might be to migrate?

If you have found the stable process that you as an attacker want to migrate to, chances are your persistence is good. Although, this may not be the case if the victim restarts his machine. What do you think a better approach would be to keep your connection persistent, even after several reboots? Try to use this method and see for yourself, if you have a persistent connection or not.

### Resources
1. [Symantec Stuxnet Dossier](http://pentest.cryptocity.net/files/operations/references/w32_stuxnet_dossier.pdf)
2. [Useful References](http://pentest.cryptocity.net/operations/references.html)


## Week 13: Application Security
In this, the last session of Hack Night. We will be going over Fuzzing and later have a short discussion on what you can do to continue improving your skills. Fuzzing is a black box software testing technique, which consists of finding implementation bugs by manipulating input data sent to an application automatically. We will go over different types of fuzzing, various methods used for fuzzing, and finally the process of "smart" fuzzing.

### Lecture Material
1. [Fuzzing](https://vimeo.com/7574602)

### Workshop Materials
1. [fuzz.py](https://github.com/isislab/Hack-Night/tree/master/2013-Fall/week13)
2. [HaikuSyscallFuzzer](https://github.com/isislab/HaikuSyscallFuzzer)

### Resources
1. [Fuzzing](https://github.com/isislab/Project-Ideas/wiki/Fuzzing)
2. [Useful References](http://pentest.cryptocity.net/fuzzing/references.html)


## Conclusion
Hack Night is designed to culminate in each student developing some kind of deliverable related to computer security, the goal being that everyone leaves the program with more knowledge about security.

### Research and Projects
1. [Project Ideas](https://github.com/isislab/Project-Ideas/issues)
2. [Project Ideas Wiki](https://github.com/isislab/Project-Ideas/wiki)
