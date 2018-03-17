#include <jni.h>

#ifndef _Included_SysInfo
#define _Included_SysInfo
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentThreadId
(JNIEnv *, jobject);
 
JNIEXPORT jstring JNICALL 
Java_systools_SysInfo_GetThreadIdString
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentProcessId
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetParentProcessId
(JNIEnv *, jobject);

JNIEXPORT jstring JNICALL 
Java_systools_SysInfo_GetProcessName
(JNIEnv *, jobject, jlong);

JNIEXPORT jstring JNICALL 
Java_systools_SysInfo_GetProcessIdString
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetSysUsedTime
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetSysIdleTime
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetThreadKernelTime
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetThreadUserTime
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentThreadKernelTime
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentThreadUserTime
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetProcessKernelTime
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetProcessUserTime
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetProcessPageFaults
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentProcessPageFaults
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentProcessKernelTime
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentProcessUserTime
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetProcessMem
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentProcessMem
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetSysVirtualMem
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetSysPhysicalMem
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetSysUsedVirtualMem
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetSysPageFaults
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetTimeNanos
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetTimeMicros
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetTotalPercentUsedCPU
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetProcessPercentUsedCPU
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetThreadPercentUsedCPU
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetActiveCPUCount
(JNIEnv *, jobject);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetUUID
(JNIEnv *, jobject, jbyteArray paramArrayOfByte);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetProcessHandles
(JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL 
Java_systools_SysInfo_GetCurrentProcessHandles
(JNIEnv *, jobject);

JNIEXPORT jstring JNICALL 
Java_systools_SysInfo_GetEnvVar
(JNIEnv *, jobject, jstring paramString);

JNIEXPORT jobjectArray JNICALL 
Java_systools_SysInfo_GetAllEnvVar
(JNIEnv *, jobject);

JNIEXPORT jstring JNICALL 
Java_systools_SysInfo_GetVersion
(JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif

