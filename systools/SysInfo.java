package systools;

import java.io.InputStream;
import java.io.PrintStream;

public class SysInfo
{
  static boolean bLibraryLoaded = false;
  
  static
  {
      System.loadLibrary("SysInfo");
      bLibraryLoaded = true;
  }
  
  public static boolean isLibraryLoaded()
  {
    return bLibraryLoaded;
  }
  
  public static long getCurrentThreadId()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentThreadId();
  }
  
  public static String getThreadIdString(long paramLong)
  {
    if (!bLibraryLoaded) {
      return null;
    }
    return GetThreadIdString(paramLong);
  }
  
  public static long getCurrentProcessId()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentProcessId();
  }
  
  public static long getParentProcessId()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetParentProcessId();
  }
  
  public static String getProcessName(long paramLong)
  {
    if (!bLibraryLoaded) {
      return null;
    }
    return GetProcessName(paramLong);
  }
  
  public static String getProcessIdString(long paramLong)
  {
    if (!bLibraryLoaded) {
      return null;
    }
    return GetProcessIdString(paramLong);
  }
  
  public static long getSysUsedTime()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetSysUsedTime();
  }
  
  public static long getSysIdleTime()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetSysIdleTime();
  }
  
  public static long getThreadKernelTime(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetThreadKernelTime(paramLong);
  }
  
  public static long getThreadUserTime(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetThreadUserTime(paramLong);
  }
  
  public static long getCurrentThreadKernelTime()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentThreadKernelTime();
  }
  
  public static long getCurrentThreadUserTime()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentThreadUserTime();
  }
  
  public static long getProcessKernelTime(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetProcessKernelTime(paramLong);
  }
  
  public static long getProcessUserTime(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetProcessUserTime(paramLong);
  }
  
  public static long getCurrentProcessKernelTime()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentProcessKernelTime();
  }
  
  public static long getCurrentProcessUserTime()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentProcessUserTime();
  }
  
  public static long getProcessMem(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetProcessMem(paramLong);
  }
  
  public static long getCurrentProcessMem()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentProcessMem();
  }
  
  public static long getProcessPageFaults(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetProcessPageFaults(paramLong);
  }
  
  public static long getCurrentProcessPageFaults()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentProcessPageFaults();
  }
  
  public static long getSysVirtualMem()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetSysVirtualMem();
  }
  
  public static long getSysPhysicalMem()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetSysPhysicalMem();
  }
  
  public static long getSysPageFaults()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetSysPageFaults();
  }
  
  public static long getSysUsedVirtualMem()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetSysUsedVirtualMem();
  }
  
  public static long getTimeNanos()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetTimeNanos();
  }
  
  public static long getTimeMicros()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetTimeMicros();
  }
  
  public static long getTotalPercentUsedCPU()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetTotalPercentUsedCPU();
  }
  
  public static long getProcessPercentUsedCPU(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetProcessPercentUsedCPU(paramLong);
  }
  
  public static long getThreadPercentUsedCPU(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetThreadPercentUsedCPU(paramLong);
  }
  
  public static long getActiveCPUCount()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetActiveCPUCount();
  }
  
  public static long getUUID(byte[] paramArrayOfByte)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetUUID(paramArrayOfByte);
  }
  
  public static long getProcessHandles(long paramLong)
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetProcessHandles(paramLong);
  }
  
  public static long getCurrentProcessHandles()
  {
    if (!bLibraryLoaded) {
      return 0L;
    }
    return GetCurrentProcessHandles();
  }
  
  public static String getEnvVar(String paramString)
  {
    if (!bLibraryLoaded) {
      return null;
    }
    return GetEnvVar(paramString);
  }
  
  public static String[] getAllEnvVar()
  {
    if (!bLibraryLoaded) {
      return null;
    }
    return GetAllEnvVar();
  }
  
  public static String getVersion()
  {
    if (!bLibraryLoaded) {
      return null;
    }
    return GetVersion();
  }
  
  public static void main(String[] paramArrayOfString)
  {
    long l1 = getCurrentProcessId();
    long l2 = getParentProcessId();
    String str1 = getProcessName(l1);
    String str2 = getProcessName(l2);
    long l3 = getCurrentThreadId();
    
    System.err.println("Library loaded "+ bLibraryLoaded);
    System.err.println("Number of Active CPUs " + getActiveCPUCount());
    System.err.println("System Physical Memory " + getSysPhysicalMem());
    System.err.println("System Virtual Memory " + getSysVirtualMem());
    System.err.println("System Used Virtual Memory " + getSysUsedVirtualMem());
    System.err.println("System Idle Time " + getSysIdleTime());
    
    System.err.println("Current Process Id " + l1);
    System.err.println("Process Id as String " + getProcessIdString(l1));
    System.err.println("Parent Process Id " + l2);
    System.err.println("Current Job Name " + str1);
    System.err.println("Parent Job Name " + str2);
    System.err.println("Current Thread Id " + l3);
    System.err.println("Thread Id as String " + getThreadIdString(l3));
    System.err.println("Current Process Handles " + getCurrentProcessHandles());
    System.err.println("System Page Faults " + getSysPageFaults());
    

    try
    {
      System.err.println("Timer Values (1 s Sleep)");
      System.err.println("MAX    9223372036854775807");
      long l4 = System.currentTimeMillis();
      long l6 = getTimeMicros();
      long l8 = getTimeNanos();
      Thread.sleep(1000L);
      l8 = getTimeNanos() - l8;
      l6 = getTimeMicros() - l6;
      l4 = System.currentTimeMillis() - l4;
      System.err.println("Nanos  " + getTimeNanos() + " delta " + l8);
      System.err.println("Micros " + getTimeMicros() + " delta " + l6);
      System.err.println("Millis " + System.currentTimeMillis() + " delta " + l4);
      
      System.err.println("Timer Values (Sequence Test)");
      for (int m = 0; m < 3; m++)
      {
        l4 = System.currentTimeMillis();
        l6 = getTimeMicros();
        l8 = getTimeNanos();
        l8 = getTimeNanos() - l8;
        l6 = getTimeMicros() - l6;
        l4 = System.currentTimeMillis() - l4;
        System.err.println("Nanos  " + getTimeNanos() + " delta " + l8);
        System.err.println("Micros " + getTimeMicros() + " delta " + l6);
        System.err.println("Millis " + System.currentTimeMillis() + " delta " + l4);
      }
    }
    catch (Exception localException1) {}
    System.err.println("Process memory " + getCurrentProcessMem() / 1024L);
    byte[] arrayOfByte2 = new byte[104857600];
    System.err.println("Process memory after 100M new " + getCurrentProcessMem() / 1024L);
    System.err.println("System Used Virtual Memory " + getSysUsedVirtualMem());
    arrayOfByte2 = null;
    System.gc();
    System.err.println("Process memory after GC " + getCurrentProcessMem() / 1024L);
    
    System.err.println("Process times (user/kernel) " + getCurrentProcessUserTime() + " " + getCurrentProcessKernelTime());
    
    System.err.println("Thread times (user/kernel) " + getCurrentThreadUserTime() + " " + getCurrentThreadKernelTime());
    
    long l5 = getCurrentProcessUserTime();
    long l7 = getCurrentProcessKernelTime();
    long l9 = getTimeNanos();
    System.err.println("Percent CPU: " +getProcessPercentUsedCPU(l1));

  }
  
  static long loopy(long paramLong)
  {
    if (paramLong < 0L) {
      return 0L;
    }
    long l = 1L;
    while (paramLong > 1L)
    {
      l *= paramLong;
      l /= paramLong;
      paramLong -= 1L;
    }
    return l;
  }
  
  public static String version = "$Revision: 1.20 $";
  
  private static native long GetCurrentThreadId();
  
  private static native String GetThreadIdString(long paramLong);
  
  private static native long GetCurrentProcessId();
  
  private static native long GetParentProcessId();
  
  private static native String GetProcessName(long paramLong);
  
  private static native String GetProcessIdString(long paramLong);
  
  private static native long GetSysUsedTime();
  
  private static native long GetSysIdleTime();
  
  private static native long GetThreadKernelTime(long paramLong);
  
  private static native long GetThreadUserTime(long paramLong);
  
  private static native long GetCurrentThreadKernelTime();
  
  private static native long GetCurrentThreadUserTime();
  
  private static native long GetProcessKernelTime(long paramLong);
  
  private static native long GetProcessUserTime(long paramLong);
  
  private static native long GetProcessPageFaults(long paramLong);
  
  private static native long GetCurrentProcessPageFaults();
  
  private static native long GetCurrentProcessKernelTime();
  
  private static native long GetCurrentProcessUserTime();
  
  private static native long GetProcessMem(long paramLong);
  
  private static native long GetCurrentProcessMem();
  
  private static native long GetSysVirtualMem();
  
  private static native long GetSysPhysicalMem();
  
  private static native long GetSysUsedVirtualMem();
  
  private static native long GetSysPageFaults();
  
  private static native long GetTimeNanos();
  
  private static native long GetTimeMicros();
  
  private static native long GetTotalPercentUsedCPU();
  
  private static native long GetProcessPercentUsedCPU(long paramLong);
  
  private static native long GetThreadPercentUsedCPU(long paramLong);
  
  private static native long GetActiveCPUCount();
  
  private static native long GetUUID(byte[] paramArrayOfByte);
  
  private static native long GetProcessHandles(long paramLong);
  
  private static native long GetCurrentProcessHandles();
  
  private static native String GetEnvVar(String paramString);
  
  private static native String[] GetAllEnvVar();
  
  private static native String GetVersion();
}
