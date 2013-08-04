# Summer Hack Night 2013 Curriculum

We're going to refer to each section of the Hack Night curriculum as a "week" because that's how we have it structured, however each topic won't necessary last a week.

[Logistics information is available here](https://github.com/isislab/Hack-Night/tree/master/2013-Summer/Logistics).

## Week 0:  [Background](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-0-background)
Just some basics here.  Watch the PicoCTF videos.  Read a bit of the textbook chapter until you get bored.  The Security Principles and the Secure Coding Principles are highly recommended, try to understand these as well as you can.  If these principles don't make sense now, they'll become clearer throughout the summer.  If reverse engineering and low level programming excite you, we recommend you watch as much of The Hardware/Software Interface class as you can, so you're ready to go when we hit week 6.

### Homework
Your homework for week 0 is this PicoCTF challenge, Python Eval 1.  Feel free to check some other easier challenges from PicoCTF as well.  Remember to use the IRC channel for questions/support.

* https://picoctf.com/problems/pyeval/stage1.html
* https://picoctf.com/registration

## Week 1:  [Introduction](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-1-introduction)
An introduction to Hack Night.  A little bit about vulnerability disclosure, and a little bit about ethics.  Two videos about what you'll learn over the summer, and how it all fits together.  The most important part of week 1 is checking out all our resources and trying to determine what you want to take away from this program.  What topics you want to focus on, what projects you want to work on, what you want to learn, what skills you want to master.

### Homework
Your homework for week 1 is to pick a project and a research topic.  This is the same task we typically give to students who are graduating from Hack Night, so if you're unsure, it's okay!  Ask a mentor in IRC for help.  We recommend you look for bugs in software, also known as vulnerability research.

* https://github.com/isislab/Project-Ideas/issues

If you cannot find a project that immediately captures your interest, just go through the list and keep it in the back of your mind while continuing the through the Hack Night curriculum.

## Week 2:  [Source Code Analysis](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-2-code-auditing)
This is an introduction to Source Code Analysis.  Watch all three lectures and check out the resources.  If you aren't familiar with [C](https://github.com/isislab/Project-Ideas/wiki/Programming#c) or [PHP](https://github.com/isislab/Project-Ideas/wiki/Programming#php), you can learn them from resources [here](https://github.com/isislab/Project-Ideas/wiki/Programming).  Don't spend too much time learning the language, just enough so you can understand the lecture.

### [Homework](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-3-code-auditing-workshop)
Try to find bugs in all three workshop materials.  Find three bugs in each assignment, then move on.  If you need any help, ask a mentor.

## Week 3:  [Web Security](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-4-web-hacking)
This is an introduction to web security.  Watch both lectures.  It helps to be familiar with web technologies, but isn't required.

### [Homework](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-5-web-hacking-workshop)
Audit all three web applications.  Find three bugs in each web application, then move on.  If you need any help or have any questions, ask a mentor.

## Week 4:  [Reverse Engineering](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-6-reverse-engineering)
During the regular semester we have 4 weeks dedicated to Reverse Engineering, however we will not be using all the materials during the summer.  Watch the three lecture videos, and then continue onto the homework.  If you particularly enjoy this topic, you can watch [Xeno's lectures](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-8-introduction-to-x86) too and do more of the [workshops](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-7-reverse-engineering-workshop) from the regular curriculum.

### [Homework](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-9-x86-split-workshop)
The homework for Reverse Engineering is to solve the first two stages of the [CMU Bomb Lab](http://csapp.cs.cmu.edu/public/1e/bomb.tar).  Use [IDA Pro](https://www.hex-rays.com/products/ida/support/download_demo.shtml) and [gdb](http://www.yolinux.com/TUTORIALS/GDB-Commands.html) to try and solve the first two phases.

## Week 5:  [Exploitation](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-10-exploiting-memory-corruption)
Watch the video, and read about the history of Exploitation.

### [Homework](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-11-exploiting-memory-corruption-workshop)
Write a fully functioning exploit for [demo.exe](http://pentest.cryptocity.net/files/exploitation/demo.zip) (Password: infected) using the video.  We have prepared [two VMs](http://isis.poly.edu/~hake/hacknight/), one with the vulnerable application and another from which you will launch your exploit.  *These Virtual Machines are for NYU Poly Hack Night use ONLY.*

## Week 6:  [Post-Exploitation](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-12-post-exploitation)
Watch the video, and read about [Stuxnet](http://pentest.cryptocity.net/files/operations/references/w32_stuxnet_dossier.pdf).

### [Homework](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#workshop-material)
Complete the workshop, using the same [VMs](http://isis.poly.edu/~hake/hacknight/).  *These Virtual Machines are for NYU Poly Hack Night use ONLY.*

## Week 7:  [Fuzzing](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#week-13-fuzzing)
Watch the video, and read about [smart](http://pages.cs.wisc.edu/~rist/642-fall-2011/toorcon.pdf) [fuzzing](http://www.uninformed.org/?v=5&a=5&t=pdf).  If this interests you, consider reading more about [Program Analysis](https://github.com/isislab/Project-Ideas/wiki/Program-Analysis).

### [Homework](https://github.com/isislab/Hack-Night/blob/master/2013-Summer/HackNight.md#workshop-materials-5)
Use [fuzz.py](https://github.com/isislab/Hack-Night/blob/master/2013-Spring/week13/fuzz.py) to fuzz mplayer or VLC, until you have one crash.

## [Final Project](https://github.com/isislab/Project-Ideas/issues)
In [week 1](https://github.com/isislab/Hack-Night/tree/master/2013-Summer/Curriculum#week-1--introduction) you started to think about a project.  At this point, you should have one in mind.  Get approval from a mentor and start your final project.  **Remember to keep us updated on your progress.**
