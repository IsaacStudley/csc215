# Chapter 11

- We are using ED

- Programs should be in all upercase since in 1983 not all terminals in circulation supported lowercase

- -V turns off numbered lines

- I (CR) puts cursor on next line

- use (CTRL I) or tab between instructions, use (cr) at end of line

- CTRL Z exits input mode

- B8T (cr) returns to beginning of text buffer

- del key erases last character entered 

- 3LT moves "cursor" down 3 Lines and Type one line

- If MIV in a line was a misinput and it was supposed to be MVI, it can be changed by SMIVctrlzMVIctrlz0LTcr

- S(Substitute)MIV(bad text)ctrlz(terminator)MVI(good text)ctrlz(terminator)0LT(puts cursor back a start and types it)

- ASM (name) compiles program and gives that name

- The .HEX file is in ASCII characters and has checksum error detection

- LOAD (name)cr puts file on disk

- CCP (name)cr