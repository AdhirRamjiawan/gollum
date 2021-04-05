╓───────────────────────────────────────────────────────╖
║              GOLLUM CREDENTIALS KEEPER                ║
╙───────────────────────────────────────────────────────╜


Features:
========
	- Small command line credential manager
	- Keeps credentials encrypted using a key and passphrase

TODO:
=====
	- Implement --pattern option for list action
	- Implement remove action
	- Encrypt Gollum file store using a key and passphrase
	- Format output on console better
	- Apply more secure programming concepts like profiling 
	  and smart pointers etc
	- Add Tiny-AES-C library to source control and reference
	  from there.
	- Update username from model to be sitename. Not storing 
	  usernames.
	- Fix bug when certain symbols are used in password that
	  wipes out file store.
	- Add high level exception handling to roll back changes
	  made to file store.
	- Clean up how we parse action options from being positional
	  to being able to access options by key-value pairs.
	- Run static analysis tools against code base

Roadmap:
=====
	- Add copy to clipboard action that takes a credential name
	  and copies your password to the Windows clipboard.
	- Password generator
	- Sync password files from some remote location. Maybe GDrive
	  or some other secure remote storage environment. FTP perhaps?
	- Maybe attempt a GUI version too at some point?