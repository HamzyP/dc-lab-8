# Lab 9 - Ex13 vs Ex14

## Ex13 (std::mutex) — dataVector(100000, 0)
```
Thread 0 duration: 36960200 nanoseconds
Thread 1 duration: 35080200 nanoseconds
Thread 2 duration: 32805100 nanoseconds
Thread 3 duration: 38548600 nanoseconds
```

## Ex14 (RWLock) — dataVector(100000, 0)

```
Thread 0 duration: 22187100 nanoseconds
Thread 1 duration: 24966600 nanoseconds
Thread 2 duration: 24204600 nanoseconds
Thread 3 duration: 25899700 nanoseconds
```

## Result/ Review

RWLock (Ex14) is ~30-35% faster than std::mutex (Ex13). Multiple readers can hold the shared lock simultaneously rather than waiting one at a time.