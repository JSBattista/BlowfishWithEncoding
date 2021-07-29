# BlowfishWithEncoding
When you want to just put some encryption in without taking a one month detour. 
Not all encryption has to last forever. Suppose you want to just send some blurb somewhere and simply don't want everybody's nose in it. Wired, wireless - it does not matter. If somebody wants to spend a day decrypting information that expires in a minute, that's their problem. 
In order to solve this small problem, without having to go with an entire encryption project, I found some "author unknown" Blowfish link at https://www.schneier.com/wp-content/uploads/2015/12/bfsh-unk.zip
It comes as one file, looks old school, and didn't compile. So I cleaned it up a bit and got that working. 

With encryption comes another problem. So you have encrypted stuff, and want to send it to a COM port that has a UART or other serial device connected. Ever print an encrypted string to console? There's beeps and bleeps and the cursor goes strange places. Those are unprintables. They can play games with transport. So you have to encode the encrypted data before you ship it. Then decode it when it gets to where your sending it. 
For encoding I found some BSD licensed code that is said to be fast. Source code has more links for credit where credit is due. 
Ultimately you will simply link header files and call the functions. The actual example you should look at is bufftest.c. Yes it's C++ code for the most part but I don't lose sleep over what extension it is. Everything could be .potato for all I care as long as it compiles. 
bufftest.c will show you what function to call for what purpose. Copy and paste as needed. Watch your lengths. The encryption segfaults if you don't allocate the buffer correctly. I did not delve into that much. Sometimes you just need to encrypt something and get it done. 
