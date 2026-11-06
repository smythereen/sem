# sem — simple System V binary locks keyed by number

`sem` wraps System V semaphores (`semget`/`semop`/`semctl`) in three
calls that work like a cross-process lock on a 32-bit key: **allocate**
(wait until free, then take), **free**, and **test**. Other units use it
when unrelated processes have to take turns on a shared resource. For
example, `map`'s `MapFileEx` locks a mapped file by its inode number.
The semaphore IDs are cached in a table inside the process, so repeated
calls do not run `semget` each time.

## What it does

- Each key gets one semaphore, created with `IPC_CREAT|0666`. A value of
  0 means free and 1 means held.
- `SemAllo(key)` performs one atomic `semop` that **blocks** until the
  value is 0 and then raises it to 1.
- `SemFree(key)` lowers the value from 1 to 0 (`IPC_NOWAIT`). If the
  semaphore is not held, it does nothing.
- `SemTest(key)` returns 0 when the lock is free with no waiters.
  Otherwise it returns `waiters + 1`.
- The private table `SemTbl` holds 10 slots. When it is full, the
  oldest released slot is reused. The private helper `SemRm` removes
  the semaphore from the system (`IPC_RMID`).

## API (`sem.h`)

```c
uchar SemAllo(u32 semkey);  /* blocks until free, then holds */
uchar SemFree(u32 semkey);  /* releases */
uchar SemTest(u32 semkey);  /* 0 = free; n = holder plus (n-1) waiters */
```

The header also defines `SEM_FREE` (0), `SEM_ALLO` (1) and
`SEM_TRC_LVL`. Private functions in `semlocal.h`: `SemGet` and
`SemRm`.

## Directory and build layout

```
sem/
  sem.h                       public header (installed to ~/cmn)
  semlocal.h                  private: sem_t, SemTbl[10], SemGet, SemRm
  semget.c semallo.c semfree.c semtest.c semrm.c   library sources
  sem.c      test program: sem a[llo]|f[ree]|g[et]|rm|t[est] <hex key>
  semcmd.c   multi-call tool: run as semallo/semfree/semtest <decimal key>;
             the upper 16 bits of the key are set to the effective UID,
             and the result is the exit code
  semsrv.c   prints SemTbl to show slot reuse and eviction
  makefile   LIBRARIES = -lsys
  UNIT.deps  base 1, require sys
```

Build inside a `base` project after `sys`: `repo add sem`, then
`make` in `sem/`.

## Example (`sem.c`, validated in a temporary copy)

```
$ sem test 7a11
26-11-05 22:01:01.180542> SemTest( 0x00007a11 ) = 0
$ sem allo 7a11
$ sem test 7a11
26-11-05 22:01:01.182363> SemTest( 0x00007a11 ) = 1
$ sem free 7a11
$ sem test 7a11
26-11-05 22:01:01.183774> SemTest( 0x00007a11 ) = 0
$ sem rm 7a11            # remove the IPC object
```

If a second process runs `sem allo 7a11` while the key is held, it
blocks until the first process frees the key.

## Dependencies

- **Direct:** `sys` only. The code uses `ErrorLog` and `Trace`
  (`SysPrt`, `LocalName`, `TraceLevel`, `TracePointer`) and the
  `common.h` types. Relink check: linking without `-lsys` fails on
  exactly those symbols. No other public unit is referenced.
- **Indirect:** none beyond sys, which has no public-unit dependencies.
- **Makefile `-l` list vs. real use:** `-lsys` matches the code's use,
  with no unused entries.

## License

The original files are offered under `Apache-2.0 OR GPL-2.0-or-later`;
you choose either license. See `LICENSE` and `LICENSES/`. Copyright
notices are retained; see the SPDX identifier in each source file.

## Version

Version tag: `v0.2.0`.
