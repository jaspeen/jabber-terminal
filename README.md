# jabber-terminal
Lightweight terminal emulator which acts as master side of pseudo terminal pair. 
So you can use text interface of any program via any jabber client. 
Since it creates a pseudo terminal for interaction with target process it able to use such commands as 'sudo' which reads password from current terminal, not from standard input.

Should work on any Posix-compatible OS and uses cross-platform gloox library for XMPP interaction.


