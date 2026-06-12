typedef int ptrdiff_t;
typedef unsigned int size_t;
typedef unsigned int wchar_t;
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short int __int16_t;
typedef short unsigned int __uint16_t;
typedef long int __int32_t;
typedef long unsigned int __uint32_t;
typedef long long int __int64_t;
typedef long long unsigned int __uint64_t;
typedef signed char __int_least8_t;
typedef unsigned char __uint_least8_t;
typedef short int __int_least16_t;
typedef short unsigned int __uint_least16_t;
typedef long int __int_least32_t;
typedef long unsigned int __uint_least32_t;
typedef long long int __int_least64_t;
typedef long long unsigned int __uint_least64_t;
typedef long long int __intmax_t;
typedef long long unsigned int __uintmax_t;
typedef int __intptr_t;
typedef unsigned int __uintptr_t;
typedef unsigned int wint_t;
typedef long __blkcnt_t;
typedef long __blksize_t;
typedef __uint64_t __fsblkcnt_t;
typedef __uint32_t __fsfilcnt_t;
typedef long _off_t;
typedef int __pid_t;
typedef short __dev_t;
typedef unsigned short __uid_t;
typedef unsigned short __gid_t;
typedef __uint32_t __id_t;
typedef unsigned short __ino_t;
typedef __uint32_t __mode_t;
__extension__ typedef long long _off64_t;
typedef _off_t __off_t;
typedef _off64_t __loff_t;
typedef long __key_t;
typedef long _fpos_t;
typedef unsigned int __size_t;
typedef signed int _ssize_t;
typedef _ssize_t __ssize_t;
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;
typedef void *_iconv_t;
typedef unsigned long __clock_t;
typedef __int_least64_t __time_t;
typedef unsigned long __clockid_t;
typedef long __daddr_t;
typedef unsigned long __timer_t;
typedef __uint8_t __sa_family_t;
typedef __uint32_t __socklen_t;
typedef int __nl_item;
typedef unsigned short __nlink_t;
typedef long __suseconds_t;
typedef unsigned long __useconds_t;
typedef __builtin_va_list __va_list;
typedef unsigned long __ULong;
struct __lock;
typedef struct __lock * _LOCK_T;
extern void __retarget_lock_init(_LOCK_T *lock);
extern void __retarget_lock_init_recursive(_LOCK_T *lock);
extern void __retarget_lock_close(_LOCK_T lock);
extern void __retarget_lock_close_recursive(_LOCK_T lock);
extern void __retarget_lock_acquire(_LOCK_T lock);
extern void __retarget_lock_acquire_recursive(_LOCK_T lock);
extern int __retarget_lock_try_acquire(_LOCK_T lock);
extern int __retarget_lock_try_acquire_recursive(_LOCK_T lock);
extern void __retarget_lock_release(_LOCK_T lock);
extern void __retarget_lock_release_recursive(_LOCK_T lock);
typedef _LOCK_T _flock_t;
struct _reent;
struct __locale_t;
struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};
struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};
struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];
 __ULong _fntypes;
 __ULong _is_cxa;
};
struct _atexit {
 struct _atexit *_next;
 int _ind;
 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
struct __sbuf {
 unsigned char *_base;
 int _size;
};
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;
  void * _cookie;
  int (*_read) (struct _reent *, void *,
        char *, int);
  int (*_write) (struct _reent *, void *,
         const char *,
         int);
  _fpos_t (*_seek) (struct _reent *, void *, _fpos_t, int);
  int (*_close) (struct _reent *, void *);
  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;
  unsigned char _ubuf[3];
  unsigned char _nbuf[1];
  struct __sbuf _lb;
  int _blksize;
  _off_t _offset;
  struct _reent *_data;
  _flock_t _lock;
  _mbstate_t _mbstate;
  int _flags2;
};
typedef struct __sFILE __FILE;
extern __FILE __sf[3];
struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
extern struct _glue __sglue;
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;
};
struct _reent
{
  int _errno;
  __FILE *_stdin, *_stdout, *_stderr;
  int _inc;
  char _emergency[25];
  struct __locale_t *_locale;
  void (*__cleanup) (struct _reent *);
  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;
  int _cvtlen;
  char *_cvtbuf;
  union
    {
      struct
        {
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
   int _h_errno;
        } _reent;
    } _new;
  void (**_sig_func)(int);
};
extern struct _reent *_impure_ptr ;
extern struct _reent _impure_data ;
extern struct _atexit *__atexit;
extern struct _atexit __atexit0;
extern void (*__stdio_exit_handler) (void);
void _reclaim_reent (struct _reent *);
extern int _fwalk_sglue (struct _reent *, int (*)(struct _reent *, __FILE *),
    struct _glue *);

extern double atan (double);
extern double cos (double);
extern double sin (double);
extern double tan (double);
extern double tanh (double);
extern double frexp (double, int *);
extern double modf (double, double *);
extern double ceil (double);
extern double fabs (double);
extern double floor (double);
extern double acos (double);
extern double asin (double);
extern double atan2 (double, double);
extern double cosh (double);
extern double sinh (double);
extern double exp (double);
extern double ldexp (double, int);
extern double log (double);
extern double log10 (double);
extern double pow (double, double);
extern double sqrt (double);
extern double fmod (double, double);
extern int finite (double);
extern int finitef (float);
extern int finitel (long double);
extern int isinff (float);
extern int isnanf (float);
extern int isinf (double);
extern int isnan (double);
    typedef float float_t;
    typedef double double_t;
extern int __isinff (float);
extern int __isinfd (double);
extern int __isnanf (float);
extern int __isnand (double);
extern int __fpclassifyf (float);
extern int __fpclassifyd (double);
extern int __signbitf (float);
extern int __signbitd (double);
extern double infinity (void);
extern double nan (const char *);
extern double copysign (double, double);
extern double logb (double);
extern int ilogb (double);
extern double asinh (double);
extern double cbrt (double);
extern double nextafter (double, double);
extern double rint (double);
extern double scalbn (double, int);
extern double exp2 (double);
extern double scalbln (double, long int);
extern double tgamma (double);
extern double nearbyint (double);
extern long int lrint (double);
extern long long int llrint (double);
extern double round (double);
extern long int lround (double);
extern long long int llround (double);
extern double trunc (double);
extern double remquo (double, double, int *);
extern double fdim (double, double);
extern double fmax (double, double);
extern double fmin (double, double);
extern double fma (double, double, double);
extern double log1p (double);
extern double expm1 (double);
extern double acosh (double);
extern double atanh (double);
extern double remainder (double, double);
extern double gamma (double);
extern double lgamma (double);
extern double erf (double);
extern double erfc (double);
extern double log2 (double);
extern double hypot (double, double);
extern float atanf (float);
extern float cosf (float);
extern float sinf (float);
extern float tanf (float);
extern float tanhf (float);
extern float frexpf (float, int *);
extern float modff (float, float *);
extern float ceilf (float);
extern float fabsf (float);
extern float floorf (float);
extern float acosf (float);
extern float asinf (float);
extern float atan2f (float, float);
extern float coshf (float);
extern float sinhf (float);
extern float expf (float);
extern float ldexpf (float, int);
extern float logf (float);
extern float log10f (float);
extern float powf (float, float);
extern float sqrtf (float);
extern float fmodf (float, float);
extern float exp2f (float);
extern float scalblnf (float, long int);
extern float tgammaf (float);
extern float nearbyintf (float);
extern long int lrintf (float);
extern long long int llrintf (float);
extern float roundf (float);
extern long int lroundf (float);
extern long long int llroundf (float);
extern float truncf (float);
extern float remquof (float, float, int *);
extern float fdimf (float, float);
extern float fmaxf (float, float);
extern float fminf (float, float);
extern float fmaf (float, float, float);
extern float infinityf (void);
extern float nanf (const char *);
extern float copysignf (float, float);
extern float logbf (float);
extern int ilogbf (float);
extern float asinhf (float);
extern float cbrtf (float);
extern float nextafterf (float, float);
extern float rintf (float);
extern float scalbnf (float, int);
extern float log1pf (float);
extern float expm1f (float);
extern float acoshf (float);
extern float atanhf (float);
extern float remainderf (float, float);
extern float gammaf (float);
extern float lgammaf (float);
extern float erff (float);
extern float erfcf (float);
extern float log2f (float);
extern float hypotf (float, float);
extern long double atanl (long double);
extern long double cosl (long double);
extern long double sinl (long double);
extern long double tanl (long double);
extern long double tanhl (long double);
extern long double frexpl (long double, int *);
extern long double modfl (long double, long double *);
extern long double ceill (long double);
extern long double fabsl (long double);
extern long double floorl (long double);
extern long double log1pl (long double);
extern long double expm1l (long double);
extern long double acosl (long double);
extern long double asinl (long double);
extern long double atan2l (long double, long double);
extern long double coshl (long double);
extern long double sinhl (long double);
extern long double expl (long double);
extern long double ldexpl (long double, int);
extern long double logl (long double);
extern long double log10l (long double);
extern long double powl (long double, long double);
extern long double sqrtl (long double);
extern long double fmodl (long double, long double);
extern long double hypotl (long double, long double);
extern long double copysignl (long double, long double);
extern long double nanl (const char *);
extern int ilogbl (long double);
extern long double asinhl (long double);
extern long double cbrtl (long double);
extern long double nextafterl (long double, long double);
extern float nexttowardf (float, long double);
extern double nexttoward (double, long double);
extern long double nexttowardl (long double, long double);
extern long double logbl (long double);
extern long double log2l (long double);
extern long double rintl (long double);
extern long double scalbnl (long double, int);
extern long double exp2l (long double);
extern long double scalblnl (long double, long);
extern long double tgammal (long double);
extern long double nearbyintl (long double);
extern long int lrintl (long double);
extern long long int llrintl (long double);
extern long double roundl (long double);
extern long lroundl (long double);
extern long long int llroundl (long double);
extern long double truncl (long double);
extern long double remquol (long double, long double, int *);
extern long double fdiml (long double, long double);
extern long double fmaxl (long double, long double);
extern long double fminl (long double, long double);
extern long double fmal (long double, long double, long double);
extern long double acoshl (long double);
extern long double atanhl (long double);
extern long double remainderl (long double, long double);
extern long double lgammal (long double);
extern long double erfl (long double);
extern long double erfcl (long double);
extern double drem (double, double);
extern float dremf (float, float);
extern double gamma_r (double, int *);
extern double lgamma_r (double, int *);
extern float gammaf_r (float, int *);
extern float lgammaf_r (float, int *);
extern double y0 (double);
extern double y1 (double);
extern double yn (int, double);
extern double j0 (double);
extern double j1 (double);
extern double jn (int, double);
extern float y0f (float);
extern float y1f (float);
extern float ynf (int, float);
extern float j0f (float);
extern float j1f (float);
extern float jnf (int, float);
extern int *__signgam (void);

typedef enum
{
  Reset_IRQn = -15,
  NonMaskableInt_IRQn = -14,
  HardFault_IRQn = -13,
  MemoryManagement_IRQn = -12,
  BusFault_IRQn = -11,
  UsageFault_IRQn = -10,
  SecureFault_IRQn = -9,
  SVCall_IRQn = -5,
  DebugMonitor_IRQn = -4,
  PendSV_IRQn = -2,
  SysTick_IRQn = -1,
  WWDG_IRQn = 0,
  PVD_AVD_IRQn = 1,
  RTC_IRQn = 2,
  RTC_S_IRQn = 3,
  TAMP_IRQn = 4,
  RAMCFG_IRQn = 5,
  FLASH_IRQn = 6,
  FLASH_S_IRQn = 7,
  GTZC_IRQn = 8,
  RCC_IRQn = 9,
  RCC_S_IRQn = 10,
  EXTI0_IRQn = 11,
  EXTI1_IRQn = 12,
  EXTI2_IRQn = 13,
  EXTI3_IRQn = 14,
  EXTI4_IRQn = 15,
  EXTI5_IRQn = 16,
  EXTI6_IRQn = 17,
  EXTI7_IRQn = 18,
  EXTI8_IRQn = 19,
  EXTI9_IRQn = 20,
  EXTI10_IRQn = 21,
  EXTI11_IRQn = 22,
  EXTI12_IRQn = 23,
  EXTI13_IRQn = 24,
  EXTI14_IRQn = 25,
  EXTI15_IRQn = 26,
  GPDMA1_Channel0_IRQn = 27,
  GPDMA1_Channel1_IRQn = 28,
  GPDMA1_Channel2_IRQn = 29,
  GPDMA1_Channel3_IRQn = 30,
  GPDMA1_Channel4_IRQn = 31,
  GPDMA1_Channel5_IRQn = 32,
  GPDMA1_Channel6_IRQn = 33,
  GPDMA1_Channel7_IRQn = 34,
  IWDG_IRQn = 35,
  SAES_IRQn = 36,
  ADC1_IRQn = 37,
  DAC1_IRQn = 38,
  FDCAN1_IT0_IRQn = 39,
  FDCAN1_IT1_IRQn = 40,
  TIM1_BRK_IRQn = 41,
  TIM1_UP_IRQn = 42,
  TIM1_TRG_COM_IRQn = 43,
  TIM1_CC_IRQn = 44,
  TIM2_IRQn = 45,
  TIM3_IRQn = 46,
  TIM4_IRQn = 47,
  TIM5_IRQn = 48,
  TIM6_IRQn = 49,
  TIM7_IRQn = 50,
  I2C1_EV_IRQn = 51,
  I2C1_ER_IRQn = 52,
  I2C2_EV_IRQn = 53,
  I2C2_ER_IRQn = 54,
  SPI1_IRQn = 55,
  SPI2_IRQn = 56,
  SPI3_IRQn = 57,
  USART1_IRQn = 58,
  USART2_IRQn = 59,
  USART3_IRQn = 60,
  UART4_IRQn = 61,
  UART5_IRQn = 62,
  LPUART1_IRQn = 63,
  LPTIM1_IRQn = 64,
  TIM8_BRK_IRQn = 65,
  TIM8_UP_IRQn = 66,
  TIM8_TRG_COM_IRQn = 67,
  TIM8_CC_IRQn = 68,
  ADC2_IRQn = 69,
  LPTIM2_IRQn = 70,
  TIM15_IRQn = 71,
  TIM16_IRQn = 72,
  TIM17_IRQn = 73,
  USB_DRD_FS_IRQn = 74,
  CRS_IRQn = 75,
  UCPD1_IRQn = 76,
  FMC_IRQn = 77,
  OCTOSPI1_IRQn = 78,
  SDMMC1_IRQn = 79,
  I2C3_EV_IRQn = 80,
  I2C3_ER_IRQn = 81,
  SPI4_IRQn = 82,
  SPI5_IRQn = 83,
  SPI6_IRQn = 84,
  USART6_IRQn = 85,
  USART10_IRQn = 86,
  USART11_IRQn = 87,
  SAI1_IRQn = 88,
  SAI2_IRQn = 89,
  GPDMA2_Channel0_IRQn = 90,
  GPDMA2_Channel1_IRQn = 91,
  GPDMA2_Channel2_IRQn = 92,
  GPDMA2_Channel3_IRQn = 93,
  GPDMA2_Channel4_IRQn = 94,
  GPDMA2_Channel5_IRQn = 95,
  GPDMA2_Channel6_IRQn = 96,
  GPDMA2_Channel7_IRQn = 97,
  UART7_IRQn = 98,
  UART8_IRQn = 99,
  UART9_IRQn = 100,
  UART12_IRQn = 101,
  SDMMC2_IRQn = 102,
  FPU_IRQn = 103,
  ICACHE_IRQn = 104,
  DCACHE1_IRQn = 105,
  ETH_IRQn = 106,
  ETH_WKUP_IRQn = 107,
  DCMI_PSSI_IRQn = 108,
  FDCAN2_IT0_IRQn = 109,
  FDCAN2_IT1_IRQn = 110,
  CORDIC_IRQn = 111,
  FMAC_IRQn = 112,
  DTS_IRQn = 113,
  RNG_IRQn = 114,
  OTFDEC1_IRQn = 115,
  AES_IRQn = 116,
  HASH_IRQn = 117,
  PKA_IRQn = 118,
  CEC_IRQn = 119,
  TIM12_IRQn = 120,
  TIM13_IRQn = 121,
  TIM14_IRQn = 122,
  I3C1_EV_IRQn = 123,
  I3C1_ER_IRQn = 124,
  I2C4_EV_IRQn = 125,
  I2C4_ER_IRQn = 126,
  LPTIM3_IRQn = 127,
  LPTIM4_IRQn = 128,
  LPTIM5_IRQn = 129,
  LPTIM6_IRQn = 130,
} IRQn_Type;
#pragma GCC diagnostic ignored "-Wpedantic"
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
typedef __int8_t int8_t ;
typedef __uint8_t uint8_t ;
typedef __int16_t int16_t ;
typedef __uint16_t uint16_t ;
typedef __int32_t int32_t ;
typedef __uint32_t uint32_t ;
typedef __int64_t int64_t ;
typedef __uint64_t uint64_t ;
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;
typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;
typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;
typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
  typedef int int_fast8_t;
  typedef unsigned int uint_fast8_t;
  typedef int int_fast16_t;
  typedef unsigned int uint_fast16_t;
  typedef int int_fast32_t;
  typedef unsigned int uint_fast32_t;
  typedef long long int int_fast64_t;
  typedef long long unsigned int uint_fast64_t;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma GCC diagnostic pop
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma GCC diagnostic pop
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma GCC diagnostic pop
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma GCC diagnostic pop
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma GCC diagnostic pop
__attribute__((always_inline)) static inline __attribute__((__noreturn__)) void __cmsis_start(void)
{
  extern void _start(void) __attribute__((__noreturn__));
  typedef struct {
    uint32_t const* src;
    uint32_t* dest;
    uint32_t wlen;
  } __copy_table_t;
  typedef struct {
    uint32_t* dest;
    uint32_t wlen;
  } __zero_table_t;
  extern const __copy_table_t __copy_table_start__;
  extern const __copy_table_t __copy_table_end__;
  extern const __zero_table_t __zero_table_start__;
  extern const __zero_table_t __zero_table_end__;
  for (__copy_table_t const* pTable = &__copy_table_start__; pTable < &__copy_table_end__; ++pTable) {
    for(uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = pTable->src[i];
    }
  }
  for (__zero_table_t const* pTable = &__zero_table_start__; pTable < &__zero_table_end__; ++pTable) {
    for(uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = 0u;
    }
  }
  _start();
}
__attribute__((always_inline)) static inline void __ISB(void)
{
  __asm volatile ("isb 0xF":::"memory");
}
__attribute__((always_inline)) static inline void __DSB(void)
{
  __asm volatile ("dsb 0xF":::"memory");
}
__attribute__((always_inline)) static inline void __DMB(void)
{
  __asm volatile ("dmb 0xF":::"memory");
}
__attribute__((always_inline)) static inline uint32_t __REV(uint32_t value)
{
  return __builtin_bswap32(value);
}
__attribute__((always_inline)) static inline uint32_t __REV16(uint32_t value)
{
  uint32_t result;
  __asm ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return result;
}
__attribute__((always_inline)) static inline int16_t __REVSH(int16_t value)
{
  return (int16_t)__builtin_bswap16(value);
}
__attribute__((always_inline)) static inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
__attribute__((always_inline)) static inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;
  uint32_t s = (4U * 8U) - 1U;
  result = value;
  for (value >>= 1U; value != 0U; value >>= 1U)
  {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;
  return result;
}
__attribute__((always_inline)) static inline uint8_t __CLZ(uint32_t value)
{
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}
__attribute__((always_inline)) static inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}
__attribute__((always_inline)) static inline uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}
__attribute__((always_inline)) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}
__attribute__((always_inline)) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}
__attribute__((always_inline)) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;
  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
__attribute__((always_inline)) static inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
  __ISB();
}
__attribute__((always_inline)) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;
  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}
__attribute__((always_inline)) static inline uint32_t __get_APSR(void)
{
  uint32_t result;
  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}
__attribute__((always_inline)) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;
  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}
__attribute__((always_inline)) static inline uint32_t __get_PSP(void)
{
  uint32_t result;
  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
__attribute__((always_inline)) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
__attribute__((always_inline)) static inline uint32_t __get_MSP(void)
{
  uint32_t result;
  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
__attribute__((always_inline)) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
__attribute__((always_inline)) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;
  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
__attribute__((always_inline)) static inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
__attribute__((always_inline)) static inline uint32_t __get_FPSCR(void)
{
  return(0U);
}
__attribute__((always_inline)) static inline void __set_FPSCR(uint32_t fpscr)
{
  (void)fpscr;
}
#pragma GCC diagnostic pop
typedef union
{
  struct
  {
    uint32_t _reserved0:16;
    uint32_t GE:4;
    uint32_t _reserved1:7;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:7;
    uint32_t GE:4;
    uint32_t _reserved1:4;
    uint32_t T:1;
    uint32_t IT:2;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;
typedef union
{
  struct
  {
    uint32_t nPRIV:1;
    uint32_t SPSEL:1;
    uint32_t FPCA:1;
    uint32_t SFPA:1;
    uint32_t _reserved1:28;
  } b;
  uint32_t w;
} CONTROL_Type;
typedef struct
{
  volatile uint32_t ISER[16U];
        uint32_t RESERVED0[16U];
  volatile uint32_t ICER[16U];
        uint32_t RSERVED1[16U];
  volatile uint32_t ISPR[16U];
        uint32_t RESERVED2[16U];
  volatile uint32_t ICPR[16U];
        uint32_t RESERVED3[16U];
  volatile uint32_t IABR[16U];
        uint32_t RESERVED4[16U];
  volatile uint32_t ITNS[16U];
        uint32_t RESERVED5[16U];
  volatile uint8_t IPR[496U];
        uint32_t RESERVED6[580U];
  volatile uint32_t STIR;
} NVIC_Type;
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;
  volatile uint32_t VTOR;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
  volatile uint8_t SHPR[12U];
  volatile uint32_t SHCSR;
  volatile uint32_t CFSR;
  volatile uint32_t HFSR;
  volatile uint32_t DFSR;
  volatile uint32_t MMFAR;
  volatile uint32_t BFAR;
  volatile uint32_t AFSR;
  volatile const uint32_t ID_PFR[2U];
  volatile const uint32_t ID_DFR;
  volatile const uint32_t ID_AFR;
  volatile const uint32_t ID_MMFR[4U];
  volatile const uint32_t ID_ISAR[6U];
  volatile const uint32_t CLIDR;
  volatile const uint32_t CTR;
  volatile const uint32_t CCSIDR;
  volatile uint32_t CSSELR;
  volatile uint32_t CPACR;
  volatile uint32_t NSACR;
        uint32_t RESERVED7[21U];
  volatile uint32_t SFSR;
  volatile uint32_t SFAR;
        uint32_t RESERVED3[69U];
  volatile uint32_t STIR;
        uint32_t RESERVED4[15U];
  volatile const uint32_t MVFR0;
  volatile const uint32_t MVFR1;
  volatile const uint32_t MVFR2;
        uint32_t RESERVED5[1U];
  volatile uint32_t ICIALLU;
        uint32_t RESERVED6[1U];
  volatile uint32_t ICIMVAU;
  volatile uint32_t DCIMVAC;
  volatile uint32_t DCISW;
  volatile uint32_t DCCMVAU;
  volatile uint32_t DCCMVAC;
  volatile uint32_t DCCSW;
  volatile uint32_t DCCIMVAC;
  volatile uint32_t DCCISW;
  volatile uint32_t BPIALL;
} SCB_Type;
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const uint32_t ICTR;
  volatile uint32_t ACTLR;
  volatile uint32_t CPPWR;
} SCnSCB_Type;
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
typedef struct
{
  volatile union
  {
    volatile uint8_t u8;
    volatile uint16_t u16;
    volatile uint32_t u32;
  } PORT [32U];
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  volatile uint32_t LAR;
  volatile const uint32_t LSR;
        uint32_t RESERVED5[1U];
  volatile const uint32_t DEVARCH;
        uint32_t RESERVED6[4U];
  volatile const uint32_t PID4;
  volatile const uint32_t PID5;
  volatile const uint32_t PID6;
  volatile const uint32_t PID7;
  volatile const uint32_t PID0;
  volatile const uint32_t PID1;
  volatile const uint32_t PID2;
  volatile const uint32_t PID3;
  volatile const uint32_t CID0;
  volatile const uint32_t CID1;
  volatile const uint32_t CID2;
  volatile const uint32_t CID3;
} ITM_Type;
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t CYCCNT;
  volatile uint32_t CPICNT;
  volatile uint32_t EXCCNT;
  volatile uint32_t SLEEPCNT;
  volatile uint32_t LSUCNT;
  volatile uint32_t FOLDCNT;
  volatile const uint32_t PCSR;
  volatile uint32_t COMP0;
        uint32_t RESERVED1[1U];
  volatile uint32_t FUNCTION0;
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP1;
        uint32_t RESERVED3[1U];
  volatile uint32_t FUNCTION1;
        uint32_t RESERVED4[1U];
  volatile uint32_t COMP2;
        uint32_t RESERVED5[1U];
  volatile uint32_t FUNCTION2;
        uint32_t RESERVED6[1U];
  volatile uint32_t COMP3;
        uint32_t RESERVED7[1U];
  volatile uint32_t FUNCTION3;
        uint32_t RESERVED8[1U];
  volatile uint32_t COMP4;
        uint32_t RESERVED9[1U];
  volatile uint32_t FUNCTION4;
        uint32_t RESERVED10[1U];
  volatile uint32_t COMP5;
        uint32_t RESERVED11[1U];
  volatile uint32_t FUNCTION5;
        uint32_t RESERVED12[1U];
  volatile uint32_t COMP6;
        uint32_t RESERVED13[1U];
  volatile uint32_t FUNCTION6;
        uint32_t RESERVED14[1U];
  volatile uint32_t COMP7;
        uint32_t RESERVED15[1U];
  volatile uint32_t FUNCTION7;
        uint32_t RESERVED16[1U];
  volatile uint32_t COMP8;
        uint32_t RESERVED17[1U];
  volatile uint32_t FUNCTION8;
        uint32_t RESERVED18[1U];
  volatile uint32_t COMP9;
        uint32_t RESERVED19[1U];
  volatile uint32_t FUNCTION9;
        uint32_t RESERVED20[1U];
  volatile uint32_t COMP10;
        uint32_t RESERVED21[1U];
  volatile uint32_t FUNCTION10;
        uint32_t RESERVED22[1U];
  volatile uint32_t COMP11;
        uint32_t RESERVED23[1U];
  volatile uint32_t FUNCTION11;
        uint32_t RESERVED24[1U];
  volatile uint32_t COMP12;
        uint32_t RESERVED25[1U];
  volatile uint32_t FUNCTION12;
        uint32_t RESERVED26[1U];
  volatile uint32_t COMP13;
        uint32_t RESERVED27[1U];
  volatile uint32_t FUNCTION13;
        uint32_t RESERVED28[1U];
  volatile uint32_t COMP14;
        uint32_t RESERVED29[1U];
  volatile uint32_t FUNCTION14;
        uint32_t RESERVED30[1U];
  volatile uint32_t COMP15;
        uint32_t RESERVED31[1U];
  volatile uint32_t FUNCTION15;
        uint32_t RESERVED32[934U];
  volatile const uint32_t LSR;
        uint32_t RESERVED33[1U];
  volatile const uint32_t DEVARCH;
} DWT_Type;
typedef struct
{
  volatile const uint32_t SSPSR;
  volatile uint32_t CSPSR;
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;
        uint32_t RESERVED2[131U];
  volatile const uint32_t FFSR;
  volatile uint32_t FFCR;
  volatile uint32_t PSCR;
        uint32_t RESERVED3[759U];
  volatile const uint32_t TRIGGER;
  volatile const uint32_t ITFTTD0;
  volatile uint32_t ITATBCTR2;
        uint32_t RESERVED4[1U];
  volatile const uint32_t ITATBCTR0;
  volatile const uint32_t ITFTTD1;
  volatile uint32_t ITCTRL;
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;
  volatile uint32_t CLAIMCLR;
        uint32_t RESERVED7[8U];
  volatile const uint32_t DEVID;
  volatile const uint32_t DEVTYPE;
} TPI_Type;
typedef struct
{
  volatile const uint32_t TYPE;
  volatile uint32_t CTRL;
  volatile uint32_t RNR;
  volatile uint32_t RBAR;
  volatile uint32_t RLAR;
  volatile uint32_t RBAR_A1;
  volatile uint32_t RLAR_A1;
  volatile uint32_t RBAR_A2;
  volatile uint32_t RLAR_A2;
  volatile uint32_t RBAR_A3;
  volatile uint32_t RLAR_A3;
        uint32_t RESERVED0[1];
  union {
  volatile uint32_t MAIR[2];
  struct {
  volatile uint32_t MAIR0;
  volatile uint32_t MAIR1;
  };
  };
} MPU_Type;
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile uint32_t FPCCR;
  volatile uint32_t FPCAR;
  volatile uint32_t FPDSCR;
  volatile const uint32_t MVFR0;
  volatile const uint32_t MVFR1;
  volatile const uint32_t MVFR2;
} FPU_Type;
typedef struct
{
  volatile uint32_t DHCSR;
  volatile uint32_t DCRSR;
  volatile uint32_t DCRDR;
  volatile uint32_t DEMCR;
        uint32_t RESERVED0[1U];
  volatile uint32_t DAUTHCTRL;
  volatile uint32_t DSCSR;
} CoreDebug_Type;
typedef struct
{
  volatile uint32_t DHCSR;
  volatile uint32_t DCRSR;
  volatile uint32_t DCRDR;
  volatile uint32_t DEMCR;
        uint32_t RESERVED0[1U];
  volatile uint32_t DAUTHCTRL;
  volatile uint32_t DSCSR;
} DCB_Type;
typedef struct
{
  volatile uint32_t DLAR;
  volatile const uint32_t DLSR;
  volatile const uint32_t DAUTHSTATUS;
  volatile const uint32_t DDEVARCH;
  volatile const uint32_t DDEVTYPE;
} DIB_Type;
static inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  reg_value = ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));
  reg_value = (reg_value |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U) );
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = reg_value;
}
static inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}
static inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __asm volatile("":::"memory");
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __asm volatile("":::"memory");
  }
}
static inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
static inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __DSB();
    __ISB();
  }
}
static inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
static inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
static inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
static inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
static inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IPR[((uint32_t)IRQn)] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
}
static inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IPR[((uint32_t)IRQn)] >> (8U - 4U)));
  }
  else
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHPR[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - 4U)));
  }
}
static inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;
  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));
  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority & (uint32_t)((1UL << (SubPriorityBits )) - 1UL)))
         );
}
static inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;
  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));
  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority = (Priority ) & (uint32_t)((1UL << (SubPriorityBits )) - 1UL);
}
static inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  vectors[(int32_t)IRQn + 16] = vector;
  __DSB();
}
static inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return vectors[(int32_t)IRQn + 16];
}
__attribute__((__noreturn__)) static inline void __NVIC_SystemReset(void)
{
  __DSB();
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = (uint32_t)((0x5FAUL << 16U) |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U) );
  __DSB();
  for(;;)
  {
    __asm volatile ("nop");
  }
}
typedef struct {
  uint32_t RBAR;
  uint32_t RLAR;
} ARM_MPU_Region_t;
static inline void ARM_MPU_Enable(uint32_t MPU_Control)
{
  __DMB();
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL = MPU_Control | (1UL );
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR |= (1UL << 16U);
  __DSB();
  __ISB();
}
static inline void ARM_MPU_Disable(void)
{
  __DMB();
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR &= ~(1UL << 16U);
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL &= ~(1UL );
  __DSB();
  __ISB();
}
static inline void ARM_MPU_SetMemAttrEx(MPU_Type* mpu, uint8_t idx, uint8_t attr)
{
  const uint8_t reg = idx / 4U;
  const uint32_t pos = ((idx % 4U) * 8U);
  const uint32_t mask = 0xFFU << pos;
  if (reg >= (sizeof(mpu->MAIR) / sizeof(mpu->MAIR[0]))) {
    return;
  }
  mpu->MAIR[reg] = ((mpu->MAIR[reg] & ~mask) | ((attr << pos) & mask));
}
static inline void ARM_MPU_SetMemAttr(uint8_t idx, uint8_t attr)
{
  ARM_MPU_SetMemAttrEx(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) ), idx, attr);
}
static inline void ARM_MPU_ClrRegionEx(MPU_Type* mpu, uint32_t rnr)
{
  mpu->RNR = rnr;
  mpu->RLAR = 0U;
}
static inline void ARM_MPU_ClrRegion(uint32_t rnr)
{
  ARM_MPU_ClrRegionEx(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) ), rnr);
}
static inline void ARM_MPU_SetRegionEx(MPU_Type* mpu, uint32_t rnr, uint32_t rbar, uint32_t rlar)
{
  mpu->RNR = rnr;
  mpu->RBAR = rbar;
  mpu->RLAR = rlar;
}
static inline void ARM_MPU_SetRegion(uint32_t rnr, uint32_t rbar, uint32_t rlar)
{
  ARM_MPU_SetRegionEx(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) ), rnr, rbar, rlar);
}
static inline void ARM_MPU_OrderedMemcpy(volatile uint32_t* dst, const uint32_t* restrict src, uint32_t len)
{
  uint32_t i;
  for (i = 0U; i < len; ++i)
  {
    dst[i] = src[i];
  }
}
static inline void ARM_MPU_LoadEx(MPU_Type* mpu, uint32_t rnr, ARM_MPU_Region_t const* table, uint32_t cnt)
{
  const uint32_t rowWordSize = sizeof(ARM_MPU_Region_t)/4U;
  if (cnt == 1U) {
    mpu->RNR = rnr;
    ARM_MPU_OrderedMemcpy(&(mpu->RBAR), &(table->RBAR), rowWordSize);
  } else {
    uint32_t rnrBase = rnr & ~(4U -1U);
    uint32_t rnrOffset = rnr % 4U;
    mpu->RNR = rnrBase;
    while ((rnrOffset + cnt) > 4U) {
      uint32_t c = 4U - rnrOffset;
      ARM_MPU_OrderedMemcpy(&(mpu->RBAR)+(rnrOffset*2U), &(table->RBAR), c*rowWordSize);
      table += c;
      cnt -= c;
      rnrOffset = 0U;
      rnrBase += 4U;
      mpu->RNR = rnrBase;
    }
    ARM_MPU_OrderedMemcpy(&(mpu->RBAR)+(rnrOffset*2U), &(table->RBAR), cnt*rowWordSize);
  }
}
static inline void ARM_MPU_Load(uint32_t rnr, ARM_MPU_Region_t const* table, uint32_t cnt)
{
  ARM_MPU_LoadEx(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) ), rnr, table, cnt);
}
static inline uint32_t SCB_GetFPUType(void)
{
  uint32_t mvfr0;
  mvfr0 = ((FPU_Type *) ((0xE000E000UL) + 0x0F30UL) )->MVFR0;
  if ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x220U)
  {
    return 2U;
  }
  else if ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x020U)
  {
    return 1U;
  }
  else
  {
    return 0U;
  }
}
static inline void DCB_SetAuthCtrl(uint32_t value)
{
    __DSB();
    __ISB();
    ((DCB_Type *) (0xE000EDF0UL) )->DAUTHCTRL = value;
    __DSB();
    __ISB();
}
static inline uint32_t DCB_GetAuthCtrl(void)
{
    return (((DCB_Type *) (0xE000EDF0UL) )->DAUTHCTRL);
}
static inline uint32_t DIB_GetAuthStatus(void)
{
    return (((DIB_Type *) (0xE000EFB0UL) )->DAUTHSTATUS);
}
static inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);
  }
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = (uint32_t)(ticks - 1UL);
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 4U) - 1UL);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0UL;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) |
                   (1UL << 1U) |
                   (1UL );
  return (0UL);
}
extern volatile int32_t ITM_RxBuffer;
static inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL ) != 0UL) )
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __asm volatile ("nop");
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}
static inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;
  if (ITM_RxBuffer != ((int32_t)0x5AA55AA5U))
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ((int32_t)0x5AA55AA5U);
  }
  return (ch);
}
static inline int32_t ITM_CheckChar (void)
{
  if (ITM_RxBuffer == ((int32_t)0x5AA55AA5U))
  {
    return (0);
  }
  else
  {
    return (1);
  }
}
extern uint32_t SystemCoreClock;
extern const uint8_t AHBPrescTable[16];
extern const uint8_t APBPrescTable[8];
extern void SystemInit (void);
extern void SystemCoreClockUpdate (void);
extern uint32_t SECURE_SystemCoreClockUpdate(void);
typedef struct
{
  volatile uint32_t DR;
  volatile uint32_t IDR;
  volatile uint32_t CR;
       uint32_t RESERVED2;
  volatile uint32_t INIT;
  volatile uint32_t POL;
} CRC_TypeDef;
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t OAR1;
  volatile uint32_t OAR2;
  volatile uint32_t TIMINGR;
  volatile uint32_t TIMEOUTR;
  volatile uint32_t ISR;
  volatile uint32_t ICR;
  volatile uint32_t PECR;
  volatile uint32_t RXDR;
  volatile uint32_t TXDR;
} I2C_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  uint32_t RESERVED1[2];
  volatile uint32_t RDR;
  volatile uint32_t RDWR;
  volatile uint32_t TDR;
  volatile uint32_t TDWR;
  volatile uint32_t IBIDR;
  volatile uint32_t TGTTDR;
  uint32_t RESERVED2[2];
  volatile uint32_t SR;
  volatile uint32_t SER;
  uint32_t RESERVED3[2];
  volatile uint32_t RMR;
  uint32_t RESERVED4[3];
  volatile uint32_t EVR;
  volatile uint32_t IER;
  volatile uint32_t CEVR;
  uint32_t RESERVED5;
  volatile uint32_t DEVR0;
  volatile uint32_t DEVRX[4];
  uint32_t RESERVED6[7];
  volatile uint32_t MAXRLR;
  volatile uint32_t MAXWLR;
  uint32_t RESERVED7[2];
  volatile uint32_t TIMINGR0;
  volatile uint32_t TIMINGR1;
  volatile uint32_t TIMINGR2;
  uint32_t RESERVED9[5];
  volatile uint32_t BCR;
  volatile uint32_t DCR;
  volatile uint32_t GETCAPR;
  volatile uint32_t CRCAPR;
  volatile uint32_t GETMXDSR;
  volatile uint32_t EPIDR;
} I3C_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;
  volatile uint32_t SR;
  volatile uint32_t CCR;
  volatile uint32_t MCR;
  volatile uint32_t SHSR1;
  volatile uint32_t SHSR2;
  volatile uint32_t SHHR;
  volatile uint32_t SHRR;
} DAC_TypeDef;
typedef struct
{
volatile uint32_t CR;
volatile uint32_t CFGR;
volatile uint32_t ISR;
volatile uint32_t ICR;
} CRS_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t DINR;
  volatile uint32_t DOUTR;
  volatile uint32_t KEYR0;
  volatile uint32_t KEYR1;
  volatile uint32_t KEYR2;
  volatile uint32_t KEYR3;
  volatile uint32_t IVR0;
  volatile uint32_t IVR1;
  volatile uint32_t IVR2;
  volatile uint32_t IVR3;
  volatile uint32_t KEYR4;
  volatile uint32_t KEYR5;
  volatile uint32_t KEYR6;
  volatile uint32_t KEYR7;
  volatile uint32_t SUSP0R;
  volatile uint32_t SUSP1R;
  volatile uint32_t SUSP2R;
  volatile uint32_t SUSP3R;
  volatile uint32_t SUSP4R;
  volatile uint32_t SUSP5R;
  volatile uint32_t SUSP6R;
  volatile uint32_t SUSP7R;
       uint32_t RESERVED1[168];
  volatile uint32_t IER;
  volatile uint32_t ISR;
  volatile uint32_t ICR;
} AES_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t DIN;
  volatile uint32_t STR;
  volatile uint32_t HRA[5];
  volatile uint32_t IMR;
  volatile uint32_t SR;
       uint32_t RESERVED[52];
  volatile uint32_t CSR[103];
} HASH_TypeDef;
typedef struct
{
  volatile uint32_t HR[16];
} HASH_DIGEST_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t NSCR;
  volatile uint32_t HTCR;
} RNG_TypeDef;
typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;
  volatile uint32_t APB1FZR1;
  volatile uint32_t APB1FZR2;
  volatile uint32_t APB2FZR;
  volatile uint32_t APB3FZR;
       uint32_t RESERVED1[2];
  volatile uint32_t AHB1FZR;
       uint32_t RESERVED2[54];
  volatile uint32_t SR;
  volatile uint32_t DBG_AUTH_HOST;
  volatile uint32_t DBG_AUTH_DEV;
  volatile uint32_t DBG_AUTH_ACK;
       uint32_t RESERVED3[945];
  volatile uint32_t PIDR4;
  volatile uint32_t PIDR5;
  volatile uint32_t PIDR6;
  volatile uint32_t PIDR7;
  volatile uint32_t PIDR0;
  volatile uint32_t PIDR1;
  volatile uint32_t PIDR2;
  volatile uint32_t PIDR3;
  volatile uint32_t CIDR0;
  volatile uint32_t CIDR1;
  volatile uint32_t CIDR2;
  volatile uint32_t CIDR3;
} DBGMCU_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t RISR;
  volatile uint32_t IER;
  volatile uint32_t MISR;
  volatile uint32_t ICR;
  volatile uint32_t ESCR;
  volatile uint32_t ESUR;
  volatile uint32_t CWSTRTR;
  volatile uint32_t CWSIZER;
  volatile uint32_t DR;
} DCMI_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t RIS;
  volatile uint32_t IER;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t RESERVED1[4];
  volatile uint32_t DR;
} PSSI_TypeDef;
typedef struct
{
  volatile uint32_t SECCFGR;
  volatile uint32_t PRIVCFGR;
  volatile uint32_t RCFGLOCKR;
  volatile uint32_t MISR;
  volatile uint32_t SMISR;
} DMA_TypeDef;
typedef struct
{
  volatile uint32_t CLBAR;
       uint32_t RESERVED1[2];
  volatile uint32_t CFCR;
  volatile uint32_t CSR;
  volatile uint32_t CCR;
       uint32_t RESERVED2[10];
  volatile uint32_t CTR1;
  volatile uint32_t CTR2;
  volatile uint32_t CBR1;
  volatile uint32_t CSAR;
  volatile uint32_t CDAR;
  volatile uint32_t CTR3;
  volatile uint32_t CBR2;
       uint32_t RESERVED3[8];
  volatile uint32_t CLLR;
} DMA_Channel_TypeDef;
typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACECR;
  volatile uint32_t MACPFR;
  volatile uint32_t MACWTR;
  volatile uint32_t MACHT0R;
  volatile uint32_t MACHT1R;
  uint32_t RESERVED1[14];
  volatile uint32_t MACVTR;
  uint32_t RESERVED2;
  volatile uint32_t MACVHTR;
  uint32_t RESERVED3;
  volatile uint32_t MACVIR;
  volatile uint32_t MACIVIR;
  uint32_t RESERVED4[2];
  volatile uint32_t MACTFCR;
  uint32_t RESERVED5[7];
  volatile uint32_t MACRFCR;
  uint32_t RESERVED6[7];
  volatile uint32_t MACISR;
  volatile uint32_t MACIER;
  volatile uint32_t MACRXTXSR;
  uint32_t RESERVED7;
  volatile uint32_t MACPCSR;
  volatile uint32_t MACRWKPFR;
  uint32_t RESERVED8[2];
  volatile uint32_t MACLCSR;
  volatile uint32_t MACLTCR;
  volatile uint32_t MACLETR;
  volatile uint32_t MAC1USTCR;
  uint32_t RESERVED9[12];
  volatile uint32_t MACVR;
  volatile uint32_t MACDR;
  uint32_t RESERVED10;
  volatile uint32_t MACHWF0R;
  volatile uint32_t MACHWF1R;
  volatile uint32_t MACHWF2R;
  uint32_t RESERVED11[54];
  volatile uint32_t MACMDIOAR;
  volatile uint32_t MACMDIODR;
  uint32_t RESERVED12[2];
  volatile uint32_t MACARPAR;
  uint32_t RESERVED13[59];
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;
  uint32_t RESERVED14[248];
  volatile uint32_t MMCCR;
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;
  uint32_t RESERVED15[14];
  volatile uint32_t MMCTSCGPR;
  volatile uint32_t MMCTMCGPR;
  uint32_t RESERVED16[5];
  volatile uint32_t MMCTPCGR;
  uint32_t RESERVED17[10];
  volatile uint32_t MMCRCRCEPR;
  volatile uint32_t MMCRAEPR;
  uint32_t RESERVED18[10];
  volatile uint32_t MMCRUPGR;
  uint32_t RESERVED19[9];
  volatile uint32_t MMCTLPIMSTR;
  volatile uint32_t MMCTLPITCR;
  volatile uint32_t MMCRLPIMSTR;
  volatile uint32_t MMCRLPITCR;
  uint32_t RESERVED20[65];
  volatile uint32_t MACL3L4C0R;
  volatile uint32_t MACL4A0R;
  uint32_t RESERVED21[2];
  volatile uint32_t MACL3A0R0R;
  volatile uint32_t MACL3A1R0R;
  volatile uint32_t MACL3A2R0R;
  volatile uint32_t MACL3A3R0R;
  uint32_t RESERVED22[4];
  volatile uint32_t MACL3L4C1R;
  volatile uint32_t MACL4A1R;
  uint32_t RESERVED23[2];
  volatile uint32_t MACL3A0R1R;
  volatile uint32_t MACL3A1R1R;
  volatile uint32_t MACL3A2R1R;
  volatile uint32_t MACL3A3R1R;
  uint32_t RESERVED24[108];
  volatile uint32_t MACTSCR;
  volatile uint32_t MACSSIR;
  volatile uint32_t MACSTSR;
  volatile uint32_t MACSTNR;
  volatile uint32_t MACSTSUR;
  volatile uint32_t MACSTNUR;
  volatile uint32_t MACTSAR;
  uint32_t RESERVED25;
  volatile uint32_t MACTSSR;
  uint32_t RESERVED26[3];
  volatile uint32_t MACTTSSNR;
  volatile uint32_t MACTTSSSR;
  uint32_t RESERVED27[2];
  volatile uint32_t MACACR;
  uint32_t RESERVED28;
  volatile uint32_t MACATSNR;
  volatile uint32_t MACATSSR;
  volatile uint32_t MACTSIACR;
  volatile uint32_t MACTSEACR;
  volatile uint32_t MACTSICNR;
  volatile uint32_t MACTSECNR;
  uint32_t RESERVED29[4];
  volatile uint32_t MACPPSCR;
  uint32_t RESERVED30[3];
  volatile uint32_t MACPPSTTSR;
  volatile uint32_t MACPPSTTNR;
  volatile uint32_t MACPPSIR;
  volatile uint32_t MACPPSWR;
  uint32_t RESERVED31[12];
  volatile uint32_t MACPOCR;
  volatile uint32_t MACSPI0R;
  volatile uint32_t MACSPI1R;
  volatile uint32_t MACSPI2R;
  volatile uint32_t MACLMIR;
  uint32_t RESERVED32[11];
  volatile uint32_t MTLOMR;
  uint32_t RESERVED33[7];
  volatile uint32_t MTLISR;
  uint32_t RESERVED34[55];
  volatile uint32_t MTLTQOMR;
  volatile uint32_t MTLTQUR;
  volatile uint32_t MTLTQDR;
  uint32_t RESERVED35[8];
  volatile uint32_t MTLQICSR;
  volatile uint32_t MTLRQOMR;
  volatile uint32_t MTLRQMPOCR;
  volatile uint32_t MTLRQDR;
  uint32_t RESERVED36[177];
  volatile uint32_t DMAMR;
  volatile uint32_t DMASBMR;
  volatile uint32_t DMAISR;
  volatile uint32_t DMADSR;
  uint32_t RESERVED37[60];
  volatile uint32_t DMACCR;
  volatile uint32_t DMACTCR;
  volatile uint32_t DMACRCR;
  uint32_t RESERVED38[2];
  volatile uint32_t DMACTDLAR;
  uint32_t RESERVED39;
  volatile uint32_t DMACRDLAR;
  volatile uint32_t DMACTDTPR;
  uint32_t RESERVED40;
  volatile uint32_t DMACRDTPR;
  volatile uint32_t DMACTDRLR;
  volatile uint32_t DMACRDRLR;
  volatile uint32_t DMACIER;
  volatile uint32_t DMACRIWTR;
  volatile uint32_t DMACSFCSR;
  uint32_t RESERVED41;
  volatile uint32_t DMACCATDR;
  uint32_t RESERVED42;
  volatile uint32_t DMACCARDR;
  uint32_t RESERVED43;
  volatile uint32_t DMACCATBR;
  uint32_t RESERVED44;
  volatile uint32_t DMACCARBR;
  volatile uint32_t DMACSR;
  uint32_t RESERVED45[2];
  volatile uint32_t DMACMFCR;
}ETH_TypeDef;
typedef struct
{
  volatile uint32_t RTSR1;
  volatile uint32_t FTSR1;
  volatile uint32_t SWIER1;
  volatile uint32_t RPR1;
  volatile uint32_t FPR1;
  volatile uint32_t SECCFGR1;
  volatile uint32_t PRIVCFGR1;
       uint32_t RESERVED1;
  volatile uint32_t RTSR2;
  volatile uint32_t FTSR2;
  volatile uint32_t SWIER2;
  volatile uint32_t RPR2;
  volatile uint32_t FPR2;
  volatile uint32_t SECCFGR2;
  volatile uint32_t PRIVCFGR2;
       uint32_t RESERVED2[9];
  volatile uint32_t EXTICR[4];
  volatile uint32_t LOCKR;
       uint32_t RESERVED3[3];
  volatile uint32_t IMR1;
  volatile uint32_t EMR1;
       uint32_t RESERVED4[2];
  volatile uint32_t IMR2;
  volatile uint32_t EMR2;
} EXTI_TypeDef;
typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t NSKEYR;
  volatile uint32_t SECKEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t NSOBKKEYR;
  volatile uint32_t SECOBKKEYR;
  volatile uint32_t OPSR;
  volatile uint32_t OPTCR;
  volatile uint32_t NSSR;
  volatile uint32_t SECSR;
  volatile uint32_t NSCR;
  volatile uint32_t SECCR;
  volatile uint32_t NSCCR;
  volatile uint32_t SECCCR;
       uint32_t RESERVED1;
  volatile uint32_t PRIVCFGR;
  volatile uint32_t NSOBKCFGR;
  volatile uint32_t SECOBKCFGR;
  volatile uint32_t HDPEXTR;
       uint32_t RESERVED2;
  volatile uint32_t OPTSR_CUR;
  volatile uint32_t OPTSR_PRG;
       uint32_t RESERVED3[2];
  volatile uint32_t NSEPOCHR_CUR;
  volatile uint32_t NSEPOCHR_PRG;
  volatile uint32_t SECEPOCHR_CUR;
  volatile uint32_t SECEPOCHR_PRG;
  volatile uint32_t OPTSR2_CUR;
  volatile uint32_t OPTSR2_PRG;
       uint32_t RESERVED4[2];
  volatile uint32_t NSBOOTR_CUR;
  volatile uint32_t NSBOOTR_PRG;
  volatile uint32_t SECBOOTR_CUR;
  volatile uint32_t SECBOOTR_PRG;
  volatile uint32_t OTPBLR_CUR;
  volatile uint32_t OTPBLR_PRG;
       uint32_t RESERVED5[2];
  volatile uint32_t SECBB1R1;
  volatile uint32_t SECBB1R2;
  volatile uint32_t SECBB1R3;
  volatile uint32_t SECBB1R4;
       uint32_t RESERVED6[4];
  volatile uint32_t PRIVBB1R1;
  volatile uint32_t PRIVBB1R2;
  volatile uint32_t PRIVBB1R3;
  volatile uint32_t PRIVBB1R4;
       uint32_t RESERVED7[4];
  volatile uint32_t SECWM1R_CUR;
  volatile uint32_t SECWM1R_PRG;
  volatile uint32_t WRP1R_CUR;
  volatile uint32_t WRP1R_PRG;
  volatile uint32_t EDATA1R_CUR;
  volatile uint32_t EDATA1R_PRG;
  volatile uint32_t HDP1R_CUR;
  volatile uint32_t HDP1R_PRG;
  volatile uint32_t ECCCORR;
  volatile uint32_t ECCDETR;
  volatile uint32_t ECCDR;
       uint32_t RESERVED8[37];
  volatile uint32_t SECBB2R1;
  volatile uint32_t SECBB2R2;
  volatile uint32_t SECBB2R3;
  volatile uint32_t SECBB2R4;
       uint32_t RESERVED9[4];
  volatile uint32_t PRIVBB2R1;
  volatile uint32_t PRIVBB2R2;
  volatile uint32_t PRIVBB2R3;
  volatile uint32_t PRIVBB2R4;
       uint32_t RESERVED10[4];
  volatile uint32_t SECWM2R_CUR;
  volatile uint32_t SECWM2R_PRG;
  volatile uint32_t WRP2R_CUR;
  volatile uint32_t WRP2R_PRG;
  volatile uint32_t EDATA2R_CUR;
  volatile uint32_t EDATA2R_PRG;
  volatile uint32_t HDP2R_CUR;
  volatile uint32_t HDP2R_PRG;
} FLASH_TypeDef;
typedef struct
{
  volatile uint32_t X1BUFCFG;
  volatile uint32_t X2BUFCFG;
  volatile uint32_t YBUFCFG;
  volatile uint32_t PARAM;
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t WDATA;
  volatile uint32_t RDATA;
} FMAC_TypeDef;
typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
  volatile uint32_t BRR;
  volatile uint32_t HSLVR;
  volatile uint32_t SECCFGR;
} GPIO_TypeDef;
typedef struct
{
  volatile uint32_t CR;
       uint32_t RESERVED1[3];
  volatile uint32_t SECCFGR1;
  volatile uint32_t SECCFGR2;
  volatile uint32_t SECCFGR3;
       uint32_t RESERVED2;
  volatile uint32_t PRIVCFGR1;
  volatile uint32_t PRIVCFGR2;
  volatile uint32_t PRIVCFGR3;
       uint32_t RESERVED3[5];
  volatile uint32_t MPCWM1ACFGR;
  volatile uint32_t MPCWM1AR;
  volatile uint32_t MPCWM1BCFGR;
  volatile uint32_t MPCWM1BR;
  volatile uint32_t MPCWM2ACFGR;
  volatile uint32_t MPCWM2AR;
  volatile uint32_t MPCWM2BCFGR;
  volatile uint32_t MPCWM2BR;
  volatile uint32_t MPCWM3ACFGR;
  volatile uint32_t MPCWM3AR;
  volatile uint32_t MPCWM3BCFGR;
  volatile uint32_t MPCWM3BR;
  volatile uint32_t MPCWM4ACFGR;
  volatile uint32_t MPCWM4AR;
  volatile uint32_t MPCWM4BCFGR;
  volatile uint32_t MPCWM4BR;
} GTZC_TZSC_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  uint32_t RESERVED1[3];
  volatile uint32_t CFGLOCKR1;
  uint32_t RESERVED2[59];
  volatile uint32_t SECCFGR[32];
  uint32_t RESERVED3[32];
  volatile uint32_t PRIVCFGR[32];
} GTZC_MPCBB_TypeDef;
typedef struct
{
  volatile uint32_t IER1;
  volatile uint32_t IER2;
  volatile uint32_t IER3;
  volatile uint32_t IER4;
  volatile uint32_t SR1;
  volatile uint32_t SR2;
  volatile uint32_t SR3;
  volatile uint32_t SR4;
  volatile uint32_t FCR1;
  volatile uint32_t FCR2;
  volatile uint32_t FCR3;
  volatile uint32_t FCR4;
} GTZC_TZIC_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t IER;
  volatile uint32_t FCR;
  volatile uint32_t HMONR;
  volatile uint32_t MMONR;
       uint32_t RESERVED1[2];
  volatile uint32_t CRR0;
  volatile uint32_t CRR1;
  volatile uint32_t CRR2;
  volatile uint32_t CRR3;
} ICACHE_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t IER;
  volatile uint32_t FCR;
  volatile uint32_t RHMONR;
  volatile uint32_t RMMONR;
       uint32_t RESERVED1[2];
  volatile uint32_t WHMONR;
  volatile uint32_t WMMONR;
  volatile uint32_t CMDRSADDRR;
  volatile uint32_t CMDREADDRR;
} DCACHE_TypeDef;
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  volatile uint32_t RCR;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t BDTR;
  volatile uint32_t CCR5;
  volatile uint32_t CCR6;
  volatile uint32_t CCMR3;
  volatile uint32_t DTR2;
  volatile uint32_t ECR;
  volatile uint32_t TISEL;
  volatile uint32_t AF1;
  volatile uint32_t AF2;
  volatile uint32_t OR1 ;
       uint32_t RESERVED0[220];
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
} TIM_TypeDef;
typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t ICR;
  volatile uint32_t DIER;
  volatile uint32_t CFGR;
  volatile uint32_t CR;
  volatile uint32_t CCR1;
  volatile uint32_t ARR;
  volatile uint32_t CNT;
  volatile uint32_t RESERVED0;
  volatile uint32_t CFGR2;
  volatile uint32_t RCR;
  volatile uint32_t CCMR1;
  volatile uint32_t RESERVED1;
  volatile uint32_t CCR2;
} LPTIM_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  uint32_t RESERVED;
  volatile uint32_t DCR1;
  volatile uint32_t DCR2;
  volatile uint32_t DCR3;
  volatile uint32_t DCR4;
  uint32_t RESERVED1[2];
  volatile uint32_t SR;
  volatile uint32_t FCR;
  uint32_t RESERVED2[6];
  volatile uint32_t DLR;
  uint32_t RESERVED3;
  volatile uint32_t AR;
  uint32_t RESERVED4;
  volatile uint32_t DR;
  uint32_t RESERVED5[11];
  volatile uint32_t PSMKR;
  uint32_t RESERVED6;
  volatile uint32_t PSMAR;
  uint32_t RESERVED7;
  volatile uint32_t PIR;
  uint32_t RESERVED8[27];
  volatile uint32_t CCR;
  uint32_t RESERVED9;
  volatile uint32_t TCR;
  uint32_t RESERVED10;
  volatile uint32_t IR;
  uint32_t RESERVED11[3];
  volatile uint32_t ABR;
  uint32_t RESERVED12[3];
  volatile uint32_t LPTR;
  uint32_t RESERVED13[3];
  volatile uint32_t WPCCR;
  uint32_t RESERVED14;
  volatile uint32_t WPTCR;
  uint32_t RESERVED15;
  volatile uint32_t WPIR;
  uint32_t RESERVED16[3];
  volatile uint32_t WPABR;
  uint32_t RESERVED17[7];
  volatile uint32_t WCCR;
  uint32_t RESERVED18;
  volatile uint32_t WTCR;
  uint32_t RESERVED19;
  volatile uint32_t WIR;
  uint32_t RESERVED20[3];
  volatile uint32_t WABR;
  uint32_t RESERVED21[23];
  volatile uint32_t HLCR;
} XSPI_TypeDef;
typedef XSPI_TypeDef OCTOSPI_TypeDef;
typedef struct
{
  volatile uint32_t REG_CONFIGR;
  volatile uint32_t REG_START_ADDR;
  volatile uint32_t REG_END_ADDR;
  volatile uint32_t REG_NONCER0;
  volatile uint32_t REG_NONCER1;
  volatile uint32_t REG_KEYR0;
  volatile uint32_t REG_KEYR1;
  volatile uint32_t REG_KEYR2;
  volatile uint32_t REG_KEYR3;
} OTFDEC_Region_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  uint32_t RESERVED1[3];
  volatile uint32_t PRIVCFGR;
  uint32_t RESERVED2[187];
  volatile uint32_t ISR;
  volatile uint32_t ICR;
  volatile uint32_t IER;
} OTFDEC_TypeDef;
typedef struct
{
  volatile uint32_t PMCR;
  volatile uint32_t PMSR;
       uint32_t RESERVED1[2];
  volatile uint32_t VOSCR;
  volatile uint32_t VOSSR;
       uint32_t RESERVED2[2];
  volatile uint32_t BDCR;
  volatile uint32_t DBPCR;
  volatile uint32_t BDSR;
  volatile uint32_t UCPDR;
  volatile uint32_t SCCR;
  volatile uint32_t VMCR;
  volatile uint32_t USBSCR;
  volatile uint32_t VMSR;
  volatile uint32_t WUSCR;
  volatile uint32_t WUSR;
  volatile uint32_t WUCR;
       uint32_t RESERVED3;
  volatile uint32_t IORETR;
       uint32_t RESERVED4[43];
  volatile uint32_t SECCFGR;
  volatile uint32_t PRIVCFGR;
}PWR_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t IER;
  volatile uint32_t ISR;
  volatile uint32_t SEAR;
  volatile uint32_t DEAR;
  volatile uint32_t ICR;
  volatile uint32_t WPR1;
  volatile uint32_t WPR2;
  uint32_t RESERVED;
  volatile uint32_t ECCKEY;
  volatile uint32_t ERKEYR;
}RAMCFG_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  uint32_t RESERVED1[3];
  volatile uint32_t HSICFGR;
  volatile uint32_t CRRCR;
  volatile uint32_t CSICFGR;
  volatile uint32_t CFGR1;
  volatile uint32_t CFGR2;
  uint32_t RESERVED2;
  volatile uint32_t PLL1CFGR;
  volatile uint32_t PLL2CFGR;
  volatile uint32_t PLL3CFGR;
  volatile uint32_t PLL1DIVR;
  volatile uint32_t PLL1FRACR;
  volatile uint32_t PLL2DIVR;
  volatile uint32_t PLL2FRACR;
  volatile uint32_t PLL3DIVR;
  volatile uint32_t PLL3FRACR;
  uint32_t RESERVED5;
  volatile uint32_t CIER;
  volatile uint32_t CIFR;
  volatile uint32_t CICR;
  uint32_t RESERVED6;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  uint32_t RESERVED7;
  volatile uint32_t AHB4RSTR;
  uint32_t RESERVED9;
  volatile uint32_t APB1LRSTR;
  volatile uint32_t APB1HRSTR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB3RSTR;
  uint32_t RESERVED10;
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  uint32_t RESERVED11;
  volatile uint32_t AHB4ENR;
  uint32_t RESERVED13;
  volatile uint32_t APB1LENR;
  volatile uint32_t APB1HENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB3ENR;
  uint32_t RESERVED14;
  volatile uint32_t AHB1LPENR;
  volatile uint32_t AHB2LPENR;
  uint32_t RESERVED15;
  volatile uint32_t AHB4LPENR;
  uint32_t RESERVED17;
  volatile uint32_t APB1LLPENR;
  volatile uint32_t APB1HLPENR;
  volatile uint32_t APB2LPENR;
  volatile uint32_t APB3LPENR;
  uint32_t RESERVED18;
  volatile uint32_t CCIPR1;
  volatile uint32_t CCIPR2;
  volatile uint32_t CCIPR3;
  volatile uint32_t CCIPR4;
  volatile uint32_t CCIPR5;
  uint32_t RESERVED19;
  volatile uint32_t BDCR;
  volatile uint32_t RSR;
  uint32_t RESERVED20[6];
  volatile uint32_t SECCFGR;
  volatile uint32_t PRIVCFGR;
} RCC_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SR;
  volatile uint32_t CLRFR;
  uint32_t Reserved[253];
  volatile uint32_t RAM[1334];
} PKA_TypeDef;
typedef struct
{
  volatile uint32_t TR;
  volatile uint32_t DR;
  volatile uint32_t SSR;
  volatile uint32_t ICSR;
  volatile uint32_t PRER;
  volatile uint32_t WUTR;
  volatile uint32_t CR;
  volatile uint32_t PRIVCFGR;
  volatile uint32_t SECCFGR;
  volatile uint32_t WPR;
  volatile uint32_t CALR;
  volatile uint32_t SHIFTR;
  volatile uint32_t TSTR;
  volatile uint32_t TSDR;
  volatile uint32_t TSSSR;
       uint32_t RESERVED0;
  volatile uint32_t ALRMAR;
  volatile uint32_t ALRMASSR;
  volatile uint32_t ALRMBR;
  volatile uint32_t ALRMBSSR;
  volatile uint32_t SR;
  volatile uint32_t MISR;
  volatile uint32_t SMISR;
  volatile uint32_t SCR;
  volatile uint32_t OR;
       uint32_t RESERVED1[3];
  volatile uint32_t ALRABINR;
  volatile uint32_t ALRBBINR;
} RTC_TypeDef;
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t FLTCR;
  volatile uint32_t ATCR1;
  volatile uint32_t ATSEEDR;
  volatile uint32_t ATOR;
  volatile uint32_t ATCR2;
  volatile uint32_t SECCFGR;
  volatile uint32_t PRIVCFGR;
       uint32_t RESERVED0;
  volatile uint32_t IER;
  volatile uint32_t SR;
  volatile uint32_t MISR;
  volatile uint32_t SMISR;
  volatile uint32_t SCR;
  volatile uint32_t COUNT1R;
       uint32_t RESERVED1[3];
  volatile uint32_t OR;
  volatile uint32_t ERCFGR;
       uint32_t RESERVED2[42];
  volatile uint32_t BKP0R;
  volatile uint32_t BKP1R;
  volatile uint32_t BKP2R;
  volatile uint32_t BKP3R;
  volatile uint32_t BKP4R;
  volatile uint32_t BKP5R;
  volatile uint32_t BKP6R;
  volatile uint32_t BKP7R;
  volatile uint32_t BKP8R;
  volatile uint32_t BKP9R;
  volatile uint32_t BKP10R;
  volatile uint32_t BKP11R;
  volatile uint32_t BKP12R;
  volatile uint32_t BKP13R;
  volatile uint32_t BKP14R;
  volatile uint32_t BKP15R;
  volatile uint32_t BKP16R;
  volatile uint32_t BKP17R;
  volatile uint32_t BKP18R;
  volatile uint32_t BKP19R;
  volatile uint32_t BKP20R;
  volatile uint32_t BKP21R;
  volatile uint32_t BKP22R;
  volatile uint32_t BKP23R;
  volatile uint32_t BKP24R;
  volatile uint32_t BKP25R;
  volatile uint32_t BKP26R;
  volatile uint32_t BKP27R;
  volatile uint32_t BKP28R;
  volatile uint32_t BKP29R;
  volatile uint32_t BKP30R;
  volatile uint32_t BKP31R;
} TAMP_TypeDef;
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t BRR;
  volatile uint32_t GTPR;
  volatile uint32_t RTOR;
  volatile uint32_t RQR;
  volatile uint32_t ISR;
  volatile uint32_t ICR;
  volatile uint32_t RDR;
  volatile uint32_t TDR;
  volatile uint32_t PRESC;
} USART_TypeDef;
typedef struct
{
  volatile uint32_t GCR;
  uint32_t RESERVED[16];
  volatile uint32_t PDMCR;
  volatile uint32_t PDMDLY;
} SAI_TypeDef;
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t FRCR;
  volatile uint32_t SLOTR;
  volatile uint32_t IMR;
  volatile uint32_t SR;
  volatile uint32_t CLRFR;
  volatile uint32_t DR;
} SAI_Block_TypeDef;
typedef struct
{
       uint32_t RESERVED1[4];
  volatile uint32_t HDPLCR;
  volatile uint32_t HDPLSR;
  volatile uint32_t NEXTHDPLCR;
  volatile uint32_t RESERVED2;
  volatile uint32_t DBGCR;
  volatile uint32_t DBGLOCKR;
       uint32_t RESERVED3[3];
  volatile uint32_t RSSCMDR;
       uint32_t RESERVED4[26];
  volatile uint32_t EPOCHSELCR;
       uint32_t RESERVED5[7];
  volatile uint32_t SECCFGR;
       uint32_t RESERVED6[15];
  volatile uint32_t PMCR;
  volatile uint32_t FPUIMR;
  volatile uint32_t MESR;
       uint32_t RESERVED7;
  volatile uint32_t CCCSR;
  volatile uint32_t CCVALR;
  volatile uint32_t CCSWCR;
  volatile uint32_t RESERVED8;
  volatile uint32_t CFGR2;
       uint32_t RESERVED9[8];
  volatile uint32_t CNSLCKR;
  volatile uint32_t CSLCKR;
  volatile uint32_t ECCNMIR;
} SBS_TypeDef;
typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  volatile uint32_t ACKTIME;
  uint32_t RESERVED0[3];
  volatile uint32_t IDMACTRL;
  volatile uint32_t IDMABSIZE;
  volatile uint32_t IDMABASER;
  uint32_t RESERVED1[2];
  volatile uint32_t IDMALAR;
  volatile uint32_t IDMABAR;
  uint32_t RESERVED2[5];
  volatile uint32_t FIFO;
} SDMMC_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
} DLYB_TypeDef;
typedef struct
{
  volatile uint32_t CFG1;
  volatile uint32_t CFG2;
  volatile uint32_t CFG3;
  volatile uint32_t CR;
  volatile uint32_t IMR;
  volatile uint32_t SR;
  volatile uint32_t ICR;
  volatile uint32_t TX_ORDSET;
  volatile uint32_t TX_PAYSZ;
  volatile uint32_t TXDR;
  volatile uint32_t RX_ORDSET;
  volatile uint32_t RX_PAYSZ;
  volatile uint32_t RXDR;
  volatile uint32_t RX_ORDEXT1;
  volatile uint32_t RX_ORDEXT2;
} UCPD_TypeDef;
typedef struct
{
  volatile uint32_t CHEP0R;
  volatile uint32_t CHEP1R;
  volatile uint32_t CHEP2R;
  volatile uint32_t CHEP3R;
  volatile uint32_t CHEP4R;
  volatile uint32_t CHEP5R;
  volatile uint32_t CHEP6R;
  volatile uint32_t CHEP7R;
  volatile uint32_t RESERVED0[8];
  volatile uint32_t CNTR;
  volatile uint32_t ISTR;
  volatile uint32_t FNR;
  volatile uint32_t DADDR;
  volatile uint32_t RESERVED1;
  volatile uint32_t LPMCSR;
  volatile uint32_t BCDR;
} USB_DRD_TypeDef;
typedef struct
{
  volatile uint32_t TXBD;
  volatile uint32_t RXBD;
} USB_DRD_PMABuffDescTypeDef;
typedef struct
{
  volatile uint32_t CREL;
  volatile uint32_t ENDN;
       uint32_t RESERVED1;
  volatile uint32_t DBTP;
  volatile uint32_t TEST;
  volatile uint32_t RWD;
  volatile uint32_t CCCR;
  volatile uint32_t NBTP;
  volatile uint32_t TSCC;
  volatile uint32_t TSCV;
  volatile uint32_t TOCC;
  volatile uint32_t TOCV;
       uint32_t RESERVED2[4];
  volatile uint32_t ECR;
  volatile uint32_t PSR;
  volatile uint32_t TDCR;
       uint32_t RESERVED3;
  volatile uint32_t IR;
  volatile uint32_t IE;
  volatile uint32_t ILS;
  volatile uint32_t ILE;
       uint32_t RESERVED4[8];
  volatile uint32_t RXGFC;
  volatile uint32_t XIDAM;
  volatile uint32_t HPMS;
       uint32_t RESERVED5;
  volatile uint32_t RXF0S;
  volatile uint32_t RXF0A;
  volatile uint32_t RXF1S;
  volatile uint32_t RXF1A;
       uint32_t RESERVED6[8];
  volatile uint32_t TXBC;
  volatile uint32_t TXFQS;
  volatile uint32_t TXBRP;
  volatile uint32_t TXBAR;
  volatile uint32_t TXBCR;
  volatile uint32_t TXBTO;
  volatile uint32_t TXBCF;
  volatile uint32_t TXBTIE;
  volatile uint32_t TXBCIE;
  volatile uint32_t TXEFS;
  volatile uint32_t TXEFA;
} FDCAN_GlobalTypeDef;
typedef struct
{
  volatile uint32_t CKDIV;
       uint32_t RESERVED1[128];
  volatile uint32_t OPTR;
       uint32_t RESERVED2[58];
  volatile uint32_t HWCFG;
  volatile uint32_t VERR;
  volatile uint32_t IPIDR;
  volatile uint32_t SIDR;
} FDCAN_Config_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t TXDR;
  volatile uint32_t RXDR;
  volatile uint32_t ISR;
  volatile uint32_t IER;
}CEC_TypeDef;
typedef struct
{
  volatile uint32_t BTCR[8];
  volatile uint32_t PCSCNTR;
} FMC_Bank1_TypeDef;
typedef struct
{
  volatile uint32_t BWTR[7];
} FMC_Bank1E_TypeDef;
typedef struct
{
  volatile uint32_t PCR;
  volatile uint32_t SR;
  volatile uint32_t PMEM;
  volatile uint32_t PATT;
  uint32_t RESERVED0;
  volatile uint32_t ECCR;
} FMC_Bank3_TypeDef;
typedef struct
{
  volatile uint32_t SDCR[2];
  volatile uint32_t SDTR[2];
  volatile uint32_t SDCMR;
  volatile uint32_t SDRTR;
  volatile uint32_t SDSR;
} FMC_Bank5_6_TypeDef;
typedef struct
{
  volatile uint32_t CSR;
  volatile uint32_t CCR;
} VREFBUF_TypeDef;
typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IER;
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CFGR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
       uint32_t RESERVED1;
  volatile uint32_t TR1;
  volatile uint32_t TR2;
  volatile uint32_t TR3;
       uint32_t RESERVED2;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t SQR4;
  volatile uint32_t DR;
       uint32_t RESERVED3;
       uint32_t RESERVED4;
  volatile uint32_t JSQR;
       uint32_t RESERVED5[4];
  volatile uint32_t OFR1;
  volatile uint32_t OFR2;
  volatile uint32_t OFR3;
  volatile uint32_t OFR4;
       uint32_t RESERVED6[4];
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
       uint32_t RESERVED7[4];
  volatile uint32_t AWD2CR;
  volatile uint32_t AWD3CR;
       uint32_t RESERVED8;
       uint32_t RESERVED9;
  volatile uint32_t DIFSEL;
  volatile uint32_t CALFACT;
       uint32_t RESERVED10[4];
  volatile uint32_t OR;
} ADC_TypeDef;
typedef struct
{
  volatile uint32_t CSR;
  uint32_t RESERVED1;
  volatile uint32_t CCR;
  volatile uint32_t CDR;
} ADC_Common_TypeDef;
typedef struct
{
  volatile uint32_t CSR;
  volatile uint32_t WDATA;
  volatile uint32_t RDATA;
} CORDIC_TypeDef;
typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
  volatile uint32_t WINR;
  volatile uint32_t EWCR;
} IWDG_TypeDef;
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CFG1;
  volatile uint32_t CFG2;
  volatile uint32_t IER;
  volatile uint32_t SR;
  volatile uint32_t IFCR;
  uint32_t RESERVED0;
  volatile uint32_t TXDR;
  uint32_t RESERVED1[3];
  volatile uint32_t RXDR;
  uint32_t RESERVED2[3];
  volatile uint32_t CRCPOLY;
  volatile uint32_t TXCRC;
  volatile uint32_t RXCRC;
  volatile uint32_t UDRDR;
  volatile uint32_t I2SCFGR;
} SPI_TypeDef;
typedef struct
{
  volatile uint32_t CFGR1;
  uint32_t RESERVED0;
  volatile uint32_t T0VALR1;
  uint32_t RESERVED1;
  volatile uint32_t RAMPVALR;
  volatile uint32_t ITR1;
  uint32_t RESERVED2;
  volatile uint32_t DR;
  volatile uint32_t SR;
  volatile uint32_t ITENR;
  volatile uint32_t ICIFR;
  volatile uint32_t OR;
}
DTS_TypeDef;
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;
typedef uint32_t (*RSSLIB_S_JumpHDPlvl2_TypeDef)(uint32_t VectorTableAddr, uint32_t MPUIndex);
typedef uint32_t (*RSSLIB_S_JumpHDPlvl3_TypeDef)(uint32_t VectorTableAddr, uint32_t MPUIndex);
typedef uint32_t (*RSSLIB_S_JumpHDPlvl3NS_TypeDef)(uint32_t VectorTableAddr);
typedef struct
{
  uint32_t *pSource;
  uint32_t *pDestination;
  uint32_t Size;
  uint32_t DoEncryption;
  uint32_t Crc;
} RSSLIB_DataProvisioningConf_t;
typedef uint32_t (*RSSLIB_NSC_DataProvisioning_TypeDef)(RSSLIB_DataProvisioningConf_t *pConfig);
typedef struct
{
  volatile const RSSLIB_S_JumpHDPlvl2_TypeDef JumpHDPLvl2;
  volatile const RSSLIB_S_JumpHDPlvl3_TypeDef JumpHDPLvl3;
  volatile const RSSLIB_S_JumpHDPlvl3NS_TypeDef JumpHDPLvl3NS;
} S_pFuncTypeDef;
typedef struct
{
  volatile const RSSLIB_NSC_DataProvisioning_TypeDef DataProvisioning;
} NSC_pFuncTypeDef;
typedef struct
{
  NSC_pFuncTypeDef NSC;
  uint32_t RESERVED1[3];
  S_pFuncTypeDef S;
}RSSLIB_pFunc_TypeDef;
typedef uint32_t (*NSSLIB_S_JumpHDPlvl2_TypeDef)(uint32_t VectorTableAddr, uint32_t MPUIndex);
typedef uint32_t (*NSSLIB_S_JumpHDPlvl3_TypeDef)(uint32_t VectorTableAddr, uint32_t MPUIndex);
typedef struct
{
  volatile const NSSLIB_S_JumpHDPlvl2_TypeDef JumpHDPLvl2;
  volatile const NSSLIB_S_JumpHDPlvl3_TypeDef JumpHDPLvl3;
} NSSLIB_pFunc_TypeDef;
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;
typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;
typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;
typedef enum
{
  HAL_OK = 0x00,
  HAL_ERROR = 0x01,
  HAL_BUSY = 0x02,
  HAL_TIMEOUT = 0x03
} HAL_StatusTypeDef;
typedef enum
{
  HAL_UNLOCKED = 0x00,
  HAL_LOCKED = 0x01
} HAL_LockTypeDef;
typedef struct
{
  uint32_t PLLState;
  uint32_t PLLSource;
  uint32_t PLLM;
  uint32_t PLLN;
  uint32_t PLLP;
  uint32_t PLLQ;
  uint32_t PLLR;
  uint32_t PLLRGE;
  uint32_t PLLVCOSEL;
  uint32_t PLLFRACN;
} RCC_PLLInitTypeDef;
typedef struct
{
  uint32_t OscillatorType;
  uint32_t HSEState;
  uint32_t LSEState;
  uint32_t HSIState;
  uint32_t HSIDiv;
  uint32_t HSICalibrationValue;
  uint32_t LSIState;
  uint32_t CSIState;
  uint32_t CSICalibrationValue;
  uint32_t HSI48State;
  RCC_PLLInitTypeDef PLL;
} RCC_OscInitTypeDef;
typedef struct
{
  uint32_t ClockType;
  uint32_t SYSCLKSource;
  uint32_t AHBCLKDivider;
  uint32_t APB1CLKDivider;
  uint32_t APB2CLKDivider;
  uint32_t APB3CLKDivider;
} RCC_ClkInitTypeDef;
typedef struct
{
  uint32_t PLL2Source;
  uint32_t PLL2M;
  uint32_t PLL2N;
  uint32_t PLL2P;
  uint32_t PLL2Q;
  uint32_t PLL2R;
  uint32_t PLL2RGE;
  uint32_t PLL2VCOSEL;
  uint32_t PLL2FRACN;
  uint32_t PLL2ClockOut;
} RCC_PLL2InitTypeDef;
typedef struct
{
  uint32_t PLL3Source;
  uint32_t PLL3M;
  uint32_t PLL3N;
  uint32_t PLL3P;
  uint32_t PLL3Q;
  uint32_t PLL3R;
  uint32_t PLL3RGE;
  uint32_t PLL3VCOSEL;
  uint32_t PLL3FRACN;
  uint32_t PLL3ClockOut;
} RCC_PLL3InitTypeDef;
typedef struct
{
  uint32_t PLL1_P_Frequency;
  uint32_t PLL1_Q_Frequency;
  uint32_t PLL1_R_Frequency;
} PLL1_ClocksTypeDef;
typedef struct
{
  uint32_t PLL2_P_Frequency;
  uint32_t PLL2_Q_Frequency;
  uint32_t PLL2_R_Frequency;
} PLL2_ClocksTypeDef;
typedef struct
{
  uint32_t PLL3_P_Frequency;
  uint32_t PLL3_Q_Frequency;
  uint32_t PLL3_R_Frequency;
} PLL3_ClocksTypeDef;
typedef struct
{
  uint64_t PeriphClockSelection;
  RCC_PLL2InitTypeDef PLL2;
  RCC_PLL3InitTypeDef PLL3;
  uint32_t CkperClockSelection;
  uint32_t Usart1ClockSelection;
  uint32_t Usart2ClockSelection;
  uint32_t Usart3ClockSelection;
  uint32_t Uart4ClockSelection;
  uint32_t Uart5ClockSelection;
  uint32_t Usart6ClockSelection;
  uint32_t Uart7ClockSelection;
  uint32_t Uart8ClockSelection;
  uint32_t Uart9ClockSelection;
  uint32_t Usart10ClockSelection;
  uint32_t Usart11ClockSelection;
  uint32_t Uart12ClockSelection;
  uint32_t Lpuart1ClockSelection;
  uint32_t I2c1ClockSelection;
  uint32_t I2c2ClockSelection;
  uint32_t I2c3ClockSelection;
  uint32_t I2c4ClockSelection;
  uint32_t I3c1ClockSelection;
  uint32_t Lptim1ClockSelection;
  uint32_t Lptim2ClockSelection;
  uint32_t Lptim3ClockSelection;
  uint32_t Lptim4ClockSelection;
  uint32_t Lptim5ClockSelection;
  uint32_t Lptim6ClockSelection;
  uint32_t FdcanClockSelection;
  uint32_t Sai1ClockSelection;
  uint32_t Sai2ClockSelection;
  uint32_t RngClockSelection;
  uint32_t Sdmmc1ClockSelection;
  uint32_t Sdmmc2ClockSelection;
  uint32_t AdcDacClockSelection;
  uint32_t DacLowPowerClockSelection;
  uint32_t OspiClockSelection;
  uint32_t Spi1ClockSelection;
  uint32_t Spi2ClockSelection;
  uint32_t Spi3ClockSelection;
  uint32_t Spi4ClockSelection;
  uint32_t Spi5ClockSelection;
  uint32_t Spi6ClockSelection;
  uint32_t RTCClockSelection;
  uint32_t CecClockSelection;
  uint32_t UsbClockSelection;
  uint32_t TimPresSelection;
} RCC_PeriphCLKInitTypeDef;
typedef struct
{
  uint32_t Prescaler;
  uint32_t Source;
  uint32_t Polarity;
  uint32_t ReloadValue;
  uint32_t ErrorLimitValue;
  uint32_t HSI48CalibrationValue;
} RCC_CRSInitTypeDef;
typedef struct
{
  uint32_t ReloadValue;
  uint32_t HSI48CalibrationValue;
  uint32_t FreqErrorCapture;
  uint32_t FreqErrorDirection;
} RCC_CRSSynchroInfoTypeDef;
HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(const RCC_PeriphCLKInitTypeDef *pPeriphClkInit);
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef *pPeriphClkInit);
uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint64_t PeriphClk);
void HAL_RCCEx_GetPLL1ClockFreq(PLL1_ClocksTypeDef *pPLL1_Clocks);
void HAL_RCCEx_GetPLL2ClockFreq(PLL2_ClocksTypeDef *pPLL2_Clocks);
void HAL_RCCEx_GetPLL3ClockFreq(PLL3_ClocksTypeDef *pPLL3_Clocks);
HAL_StatusTypeDef HAL_RCCEx_EnablePLL2(RCC_PLL2InitTypeDef *pPLL2Init);
HAL_StatusTypeDef HAL_RCCEx_DisablePLL2(void);
HAL_StatusTypeDef HAL_RCCEx_EnablePLL3(RCC_PLL3InitTypeDef *pPLL3Init);
HAL_StatusTypeDef HAL_RCCEx_DisablePLL3(void);
void HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk);
void HAL_RCCEx_KerWakeUpStopCLKConfig(uint32_t WakeUpClk);
void HAL_RCCEx_EnableLSECSS(void);
void HAL_RCCEx_DisableLSECSS(void);
void HAL_RCCEx_LSECSS_IRQHandler(void);
void HAL_RCCEx_LSECSS_Callback(void);
void HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void HAL_RCCEx_DisableLSCO(void);
void HAL_RCCEx_CRSConfig(const RCC_CRSInitTypeDef *pInit);
void HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void);
void HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo);
uint32_t HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout);
void HAL_RCCEx_CRS_IRQHandler(void);
void HAL_RCCEx_CRS_SyncOkCallback(void);
void HAL_RCCEx_CRS_SyncWarnCallback(void);
void HAL_RCCEx_CRS_ExpectedSyncCallback(void);
void HAL_RCCEx_CRS_ErrorCallback(uint32_t Error);
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *pOscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *pClkInitStruct, uint32_t FLatency);
void HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void HAL_RCC_EnableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
uint32_t HAL_RCC_GetPCLK3Freq(void);
void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *pOscInitStruct);
void HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *pClkInitStruct, uint32_t *pFLatency);
void HAL_RCC_NMI_IRQHandler(void);
void HAL_RCC_CSSCallback(void);
uint32_t HAL_RCC_GetResetSource(void);
void HAL_RCC_ConfigAttributes(uint32_t Item, uint32_t Attributes);
HAL_StatusTypeDef HAL_RCC_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);
typedef struct
{
  uint32_t Pin;
  uint32_t Mode;
  uint32_t Pull;
  uint32_t Speed;
  uint32_t Alternate;
} GPIO_InitTypeDef;
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, const GPIO_InitTypeDef *pGPIO_Init);
void HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);
GPIO_PinState HAL_GPIO_ReadPin(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EnableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_DisableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);
typedef struct
{
  uint32_t BaseAddress;
  uint32_t RemapAddress;
  uint32_t Size;
  uint32_t TrafficRoute;
  uint32_t OutputBurstType;
} ICACHE_RegionConfigTypeDef;
HAL_StatusTypeDef HAL_ICACHE_Enable(void);
HAL_StatusTypeDef HAL_ICACHE_Disable(void);
uint32_t HAL_ICACHE_IsEnabled(void);
HAL_StatusTypeDef HAL_ICACHE_ConfigAssociativityMode(uint32_t AssociativityMode);
HAL_StatusTypeDef HAL_ICACHE_DeInit(void);
HAL_StatusTypeDef HAL_ICACHE_Invalidate(void);
HAL_StatusTypeDef HAL_ICACHE_Invalidate_IT(void);
HAL_StatusTypeDef HAL_ICACHE_WaitForInvalidateComplete(void);
HAL_StatusTypeDef HAL_ICACHE_Monitor_Start(uint32_t MonitorType);
HAL_StatusTypeDef HAL_ICACHE_Monitor_Stop(uint32_t MonitorType);
HAL_StatusTypeDef HAL_ICACHE_Monitor_Reset(uint32_t MonitorType);
uint32_t HAL_ICACHE_Monitor_GetHitValue(void);
uint32_t HAL_ICACHE_Monitor_GetMissValue(void);
void HAL_ICACHE_IRQHandler(void);
void HAL_ICACHE_InvalidateCompleteCallback(void);
void HAL_ICACHE_ErrorCallback(void);
HAL_StatusTypeDef HAL_ICACHE_EnableRemapRegion(uint32_t Region, const ICACHE_RegionConfigTypeDef *const pRegionConfig);
HAL_StatusTypeDef HAL_ICACHE_DisableRemapRegion(uint32_t Region);
typedef struct
{
  uint32_t MPCBB_SecConfig_array[(32U)];
  uint32_t MPCBB_PrivConfig_array[(32U)];
  uint32_t MPCBB_LockConfig_array[(1U)];
} MPCBB_Attribute_ConfigTypeDef;
typedef struct
{
  uint32_t SecureRWIllegalMode;
  uint32_t InvertSecureState;
  MPCBB_Attribute_ConfigTypeDef AttributeConfig;
} MPCBB_ConfigTypeDef;
typedef struct
{
  uint32_t AreaId;
  uint32_t Offset;
  uint32_t Length;
  uint32_t Attribute;
  uint32_t Lock;
  uint32_t AreaStatus;
} MPCWM_ConfigTypeDef;
HAL_StatusTypeDef HAL_GTZC_TZSC_ConfigPeriphAttributes(uint32_t PeriphId,
                                                       uint32_t PeriphAttributes);
HAL_StatusTypeDef HAL_GTZC_TZSC_GetConfigPeriphAttributes(uint32_t PeriphId,
                                                          uint32_t *PeriphAttributes);
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes(uint32_t MemBaseAddress,
                                                          const MPCWM_ConfigTypeDef *pMPCWM_Desc);
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes(uint32_t MemBaseAddress,
                                                             MPCWM_ConfigTypeDef *pMPCWM_Desc);
HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMem(uint32_t MemBaseAddress,
                                           const MPCBB_ConfigTypeDef *pMPCBB_desc);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMem(uint32_t MemBaseAddress,
                                              MPCBB_ConfigTypeDef *pMPCBB_desc);
HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMemAttributes(uint32_t MemAddress,
                                                     uint32_t NbBlocks,
                                                     const uint32_t *pMemAttributes);
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMemAttributes(uint32_t MemAddress,
                                                        uint32_t NbBlocks,
                                                        uint32_t *pMemAttributes);
typedef struct
{
  uint32_t Request;
  uint32_t BlkHWRequest;
  uint32_t Direction;
  uint32_t SrcInc;
  uint32_t DestInc;
  uint32_t SrcDataWidth;
  uint32_t DestDataWidth;
  uint32_t Priority;
  uint32_t SrcBurstLength;
  uint32_t DestBurstLength;
  uint32_t TransferAllocatedPort;
  uint32_t TransferEventMode;
  uint32_t Mode;
} DMA_InitTypeDef;
typedef struct
{
  uint32_t Priority;
  uint32_t LinkStepMode;
  uint32_t LinkAllocatedPort;
  uint32_t TransferEventMode;
  uint32_t LinkedListMode;
} DMA_InitLinkedListTypeDef;
typedef enum
{
  HAL_DMA_STATE_RESET = 0x00U,
  HAL_DMA_STATE_READY = 0x01U,
  HAL_DMA_STATE_BUSY = 0x02U,
  HAL_DMA_STATE_ERROR = 0x03U,
  HAL_DMA_STATE_ABORT = 0x04U,
  HAL_DMA_STATE_SUSPEND = 0x05U,
} HAL_DMA_StateTypeDef;
typedef enum
{
  HAL_DMA_FULL_TRANSFER = 0x00U,
  HAL_DMA_HALF_TRANSFER = 0x01U,
} HAL_DMA_LevelCompleteTypeDef;
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID = 0x00U,
  HAL_DMA_XFER_HALFCPLT_CB_ID = 0x01U,
  HAL_DMA_XFER_ERROR_CB_ID = 0x02U,
  HAL_DMA_XFER_ABORT_CB_ID = 0x03U,
  HAL_DMA_XFER_SUSPEND_CB_ID = 0x04U,
  HAL_DMA_XFER_ALL_CB_ID = 0x05U
} HAL_DMA_CallbackIDTypeDef;
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef *Instance;
  DMA_InitTypeDef Init;
  DMA_InitLinkedListTypeDef InitLinkedList;
  HAL_LockTypeDef Lock;
  uint32_t Mode;
  volatile HAL_DMA_StateTypeDef State;
  volatile uint32_t ErrorCode;
  void *Parent;
  void (* XferCpltCallback)(struct __DMA_HandleTypeDef *hdma);
  void (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef *hdma);
  void (* XferErrorCallback)(struct __DMA_HandleTypeDef *hdma);
  void (* XferAbortCallback)(struct __DMA_HandleTypeDef *hdma);
  void (* XferSuspendCallback)(struct __DMA_HandleTypeDef *hdma);
  struct __DMA_QListTypeDef *LinkedListQueue;
} DMA_HandleTypeDef;
typedef struct
{
  uint32_t DataExchange;
  uint32_t DataAlignment;
} DMA_DataHandlingConfTypeDef;
typedef struct
{
  uint32_t TriggerMode;
  uint32_t TriggerPolarity;
  uint32_t TriggerSelection;
} DMA_TriggerConfTypeDef;
typedef struct
{
  uint32_t RepeatCount;
  int32_t SrcAddrOffset;
  int32_t DestAddrOffset;
  int32_t BlkSrcAddrOffset;
  int32_t BlkDestAddrOffset;
} DMA_RepeatBlockConfTypeDef;
typedef enum
{
  HAL_DMA_QUEUE_STATE_RESET = 0x00U,
  HAL_DMA_QUEUE_STATE_READY = 0x01U,
  HAL_DMA_QUEUE_STATE_BUSY = 0x02U
} HAL_DMA_QStateTypeDef;
typedef struct
{
  uint32_t NodeType;
  DMA_InitTypeDef Init;
  DMA_DataHandlingConfTypeDef DataHandlingConfig;
  DMA_TriggerConfTypeDef TriggerConfig;
  DMA_RepeatBlockConfTypeDef RepeatBlockConfig;
  uint32_t SrcAddress;
  uint32_t DstAddress;
  uint32_t DataSize;
} DMA_NodeConfTypeDef;
typedef struct
{
  uint32_t LinkRegisters[8U];
  uint32_t NodeInfo;
} DMA_NodeTypeDef;
typedef struct __DMA_QListTypeDef
{
  DMA_NodeTypeDef *Head;
  DMA_NodeTypeDef *FirstCircularNode;
  uint32_t NodeNumber;
  volatile HAL_DMA_QStateTypeDef State;
  volatile uint32_t ErrorCode;
  volatile uint32_t Type;
} DMA_QListTypeDef;
HAL_StatusTypeDef HAL_DMAEx_List_Init(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMAEx_List_DeInit(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMAEx_List_Start(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMAEx_List_Start_IT(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMAEx_List_BuildNode(DMA_NodeConfTypeDef const *const pNodeConfig,
                                           DMA_NodeTypeDef *const pNode);
HAL_StatusTypeDef HAL_DMAEx_List_GetNodeConfig(DMA_NodeConfTypeDef *const pNodeConfig,
                                               DMA_NodeTypeDef const *const pNode);
HAL_StatusTypeDef HAL_DMAEx_List_InsertNode(DMA_QListTypeDef *const pQList,
                                            DMA_NodeTypeDef *const pPrevNode,
                                            DMA_NodeTypeDef *const pNewNode);
HAL_StatusTypeDef HAL_DMAEx_List_InsertNode_Head(DMA_QListTypeDef *const pQList,
                                                 DMA_NodeTypeDef *const pNewNode);
HAL_StatusTypeDef HAL_DMAEx_List_InsertNode_Tail(DMA_QListTypeDef *const pQList,
                                                 DMA_NodeTypeDef *const pNewNode);
HAL_StatusTypeDef HAL_DMAEx_List_RemoveNode(DMA_QListTypeDef *const pQList,
                                            DMA_NodeTypeDef *const pNode);
HAL_StatusTypeDef HAL_DMAEx_List_RemoveNode_Head(DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_RemoveNode_Tail(DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_ReplaceNode(DMA_QListTypeDef *const pQList,
                                             DMA_NodeTypeDef *const pOldNode,
                                             DMA_NodeTypeDef *const pNewNode);
HAL_StatusTypeDef HAL_DMAEx_List_ReplaceNode_Head(DMA_QListTypeDef *const pQList,
                                                  DMA_NodeTypeDef *const pNewNode);
HAL_StatusTypeDef HAL_DMAEx_List_ReplaceNode_Tail(DMA_QListTypeDef *const pQList,
                                                  DMA_NodeTypeDef *const pNewNode);
HAL_StatusTypeDef HAL_DMAEx_List_ResetQ(DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_InsertQ(DMA_QListTypeDef *const pSrcQList,
                                         DMA_NodeTypeDef const *const pPrevNode,
                                         DMA_QListTypeDef *const pDestQList);
HAL_StatusTypeDef HAL_DMAEx_List_InsertQ_Head(DMA_QListTypeDef *const pSrcQList,
                                              DMA_QListTypeDef *const pDestQList);
HAL_StatusTypeDef HAL_DMAEx_List_InsertQ_Tail(DMA_QListTypeDef *const pSrcQList,
                                              DMA_QListTypeDef *const pDestQList);
HAL_StatusTypeDef HAL_DMAEx_List_SetCircularModeConfig(DMA_QListTypeDef *const pQList,
                                                       DMA_NodeTypeDef *const pFirstCircularNode);
HAL_StatusTypeDef HAL_DMAEx_List_SetCircularMode(DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_ClearCircularMode(DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_ConvertQToDynamic(DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_ConvertQToStatic(DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_LinkQ(DMA_HandleTypeDef *const hdma,
                                       DMA_QListTypeDef *const pQList);
HAL_StatusTypeDef HAL_DMAEx_List_UnLinkQ(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMAEx_ConfigDataHandling(DMA_HandleTypeDef *const hdma,
                                               DMA_DataHandlingConfTypeDef const *const pConfigDataHandling);
HAL_StatusTypeDef HAL_DMAEx_ConfigTrigger(DMA_HandleTypeDef *const hdma,
                                          DMA_TriggerConfTypeDef const *const pConfigTrigger);
HAL_StatusTypeDef HAL_DMAEx_ConfigRepeatBlock(DMA_HandleTypeDef *const hdma,
                                              DMA_RepeatBlockConfTypeDef const *const pConfigRepeatBlock);
HAL_StatusTypeDef HAL_DMAEx_Suspend(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMAEx_Suspend_IT(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMAEx_Resume(DMA_HandleTypeDef *const hdma);
uint32_t HAL_DMAEx_GetFifoLevel(DMA_HandleTypeDef const *const hdma);
typedef struct
{
  uint32_t cllr_offset;
  uint32_t previousnode_addr;
  uint32_t currentnode_pos;
  uint32_t currentnode_addr;
  uint32_t nextnode_addr;
} DMA_NodeInQInfoTypeDef;
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *const hdma,
                                uint32_t SrcAddress,
                                uint32_t DstAddress,
                                uint32_t SrcDataSize);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *const hdma,
                                   uint32_t SrcAddress,
                                   uint32_t DstAddress,
                                   uint32_t SrcDataSize);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *const hdma,
                                          HAL_DMA_LevelCompleteTypeDef CompleteLevel,
                                          uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *const hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *const hdma,
                                           HAL_DMA_CallbackIDTypeDef CallbackID,
                                           void (*const pCallback)(DMA_HandleTypeDef *const _hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *const hdma,
                                             HAL_DMA_CallbackIDTypeDef CallbackID);
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef const *const hdma);
uint32_t HAL_DMA_GetError(DMA_HandleTypeDef const *const hdma);
HAL_StatusTypeDef HAL_DMA_ConfigChannelAttributes(DMA_HandleTypeDef *const hdma,
                                                  uint32_t ChannelAttributes);
HAL_StatusTypeDef HAL_DMA_GetConfigChannelAttributes(DMA_HandleTypeDef const *const hdma,
                                                     uint32_t *const pChannelAttributes);
HAL_StatusTypeDef HAL_DMA_GetLockChannelAttributes(DMA_HandleTypeDef const *const hdma,
                                                   uint32_t *const pLockState);
typedef struct
{
  uint8_t Enable;
  uint8_t Number;
  uint32_t BaseAddress;
  uint32_t LimitAddress;
  uint8_t AttributesIndex;
  uint8_t AccessPermission;
  uint8_t DisableExec;
  uint8_t IsShareable;
} MPU_Region_InitTypeDef;
typedef struct
{
  uint8_t Number;
  uint8_t Attributes;
} MPU_Attributes_InitTypeDef;
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *const pPreemptPriority,
                          uint32_t *const pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
uint32_t HAL_SYSTICK_GetCLKSourceConfig(void);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);
void HAL_MPU_Enable(uint32_t MPU_Control);
void HAL_MPU_Disable(void);
void HAL_MPU_EnableRegion(uint32_t RegionNumber);
void HAL_MPU_DisableRegion(uint32_t RegionNumber);
void HAL_MPU_ConfigRegion(const MPU_Region_InitTypeDef *const pMPU_RegionInit);
void HAL_MPU_ConfigMemoryAttributes(const MPU_Attributes_InitTypeDef *const pMPU_AttributesInit);
typedef enum
{
  HAL_PKA_STATE_RESET = 0x00U,
  HAL_PKA_STATE_READY = 0x01U,
  HAL_PKA_STATE_BUSY = 0x02U,
  HAL_PKA_STATE_ERROR = 0x03U,
}
HAL_PKA_StateTypeDef;
typedef struct
{
  PKA_TypeDef *Instance;
  volatile HAL_PKA_StateTypeDef State;
  volatile uint32_t ErrorCode;
  volatile uint32_t primeordersize;
  volatile uint32_t opsize;
  volatile uint32_t modulussize;
} PKA_HandleTypeDef;
typedef struct
{
  uint32_t scalarMulSize;
  uint32_t modulusSize;
  uint32_t coefSign;
  const uint8_t *coefA;
  const uint8_t *coefB;
  const uint8_t *modulus;
  const uint8_t *pointX;
  const uint8_t *pointY;
  const uint8_t *scalarMul;
  const uint8_t *primeOrder;
} PKA_ECCMulInTypeDef;
typedef struct
{
  uint32_t primeOrderSize;
  uint32_t scalarMulSize;
  uint32_t modulusSize;
  uint32_t coefSign;
  const uint8_t *coefA;
  const uint8_t *coefB;
  const uint8_t *modulus;
  const uint8_t *pointX;
  const uint8_t *pointY;
  const uint8_t *scalarMul;
  const uint8_t *primeOrder;
} PKA_ECCMulExInTypeDef;
typedef struct
{
  uint32_t modulusSize;
  uint32_t coefSign;
  const uint8_t *coefA;
  const uint8_t *coefB;
  const uint8_t *modulus;
  const uint8_t *pointX;
  const uint8_t *pointY;
  const uint32_t *pMontgomeryParam;
} PKA_PointCheckInTypeDef;
typedef struct
{
  uint32_t size;
  const uint8_t *pOpDp;
  const uint8_t *pOpDq;
  const uint8_t *pOpQinv;
  const uint8_t *pPrimeP;
  const uint8_t *pPrimeQ;
  const uint8_t *popA;
} PKA_RSACRTExpInTypeDef;
typedef struct
{
  uint32_t primeOrderSize;
  uint32_t modulusSize;
  uint32_t coefSign;
  const uint8_t *coef;
  const uint8_t *modulus;
  const uint8_t *basePointX;
  const uint8_t *basePointY;
  const uint8_t *pPubKeyCurvePtX;
  const uint8_t *pPubKeyCurvePtY;
  const uint8_t *RSign;
  const uint8_t *SSign;
  const uint8_t *hash;
  const uint8_t *primeOrder;
} PKA_ECDSAVerifInTypeDef;
typedef struct
{
  uint32_t primeOrderSize;
  uint32_t modulusSize;
  uint32_t coefSign;
  const uint8_t *coef;
  const uint8_t *coefB;
  const uint8_t *modulus;
  const uint8_t *integer;
  const uint8_t *basePointX;
  const uint8_t *basePointY;
  const uint8_t *hash;
  const uint8_t *privateKey;
  const uint8_t *primeOrder;
} PKA_ECDSASignInTypeDef;
typedef struct
{
  uint8_t *RSign;
  uint8_t *SSign;
} PKA_ECDSASignOutTypeDef;
typedef struct
{
  uint8_t *ptX;
  uint8_t *ptY;
} PKA_ECDSASignOutExtParamTypeDef, PKA_ECCMulOutTypeDef, PKA_ECCProjective2AffineOutTypeDef,
PKA_ECCDoubleBaseLadderOutTypeDef;
typedef struct
{
  uint8_t *ptX;
  uint8_t *ptY;
  uint8_t *ptZ;
} PKA_ECCCompleteAdditionOutTypeDef;
typedef struct
{
  uint32_t expSize;
  uint32_t OpSize;
  const uint8_t *pExp;
  const uint8_t *pOp1;
  const uint8_t *pMod;
} PKA_ModExpInTypeDef;
typedef struct
{
  uint32_t expSize;
  uint32_t OpSize;
  const uint8_t *pOp1;
  const uint8_t *pExp;
  const uint8_t *pMod;
  const uint8_t *pPhi;
} PKA_ModExpProtectModeInTypeDef;
typedef struct
{
  uint32_t expSize;
  uint32_t OpSize;
  const uint8_t *pExp;
  const uint8_t *pOp1;
  const uint8_t *pMod;
  const uint32_t *pMontgomeryParam;
} PKA_ModExpFastModeInTypeDef;
typedef struct
{
  uint32_t size;
  const uint8_t *pOp1;
} PKA_MontgomeryParamInTypeDef;
typedef struct
{
  uint32_t size;
  const uint32_t *pOp1;
  const uint32_t *pOp2;
} PKA_AddInTypeDef, PKA_SubInTypeDef, PKA_MulInTypeDef, PKA_CmpInTypeDef;
typedef struct
{
  uint32_t size;
  const uint32_t *pOp1;
  const uint8_t *pMod;
} PKA_ModInvInTypeDef;
typedef struct
{
  uint32_t OpSize;
  uint32_t modSize;
  const uint32_t *pOp1;
  const uint8_t *pMod;
} PKA_ModRedInTypeDef;
typedef struct
{
  uint32_t size;
  const uint32_t *pOp1;
  const uint32_t *pOp2;
  const uint8_t *pOp3;
} PKA_ModAddInTypeDef, PKA_ModSubInTypeDef, PKA_MontgomeryMulInTypeDef;
typedef struct
{
  uint32_t primeOrderSize;
  uint32_t modulusSize;
  uint32_t coefSign;
  const uint8_t *coefA;
  const uint8_t *modulus;
  const uint8_t *integerK;
  const uint8_t *integerM;
  const uint8_t *basePointX1;
  const uint8_t *basePointY1;
  const uint8_t *basePointZ1;
  const uint8_t *basePointX2;
  const uint8_t *basePointY2;
  const uint8_t *basePointZ2;
} PKA_ECCDoubleBaseLadderInTypeDef;
typedef struct
{
  uint32_t modulusSize;
  const uint8_t *modulus;
  const uint8_t *basePointX;
  const uint8_t *basePointY;
  const uint8_t *basePointZ;
  const uint32_t *pMontgomeryParam;
} PKA_ECCProjective2AffineInTypeDef;
typedef struct
{
  uint32_t modulusSize;
  uint32_t coefSign;
  const uint8_t *modulus;
  const uint8_t *coefA;
  const uint8_t *basePointX1;
  const uint8_t *basePointY1;
  const uint8_t *basePointZ1;
  const uint8_t *basePointX2;
  const uint8_t *basePointY2;
  const uint8_t *basePointZ2;
} PKA_ECCCompleteAdditionInTypeDef;
HAL_StatusTypeDef HAL_PKA_Init(PKA_HandleTypeDef *hpka);
HAL_StatusTypeDef HAL_PKA_DeInit(PKA_HandleTypeDef *hpka);
void HAL_PKA_MspInit(PKA_HandleTypeDef *hpka);
void HAL_PKA_MspDeInit(PKA_HandleTypeDef *hpka);
HAL_StatusTypeDef HAL_PKA_ModExp(PKA_HandleTypeDef *hpka, PKA_ModExpInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ModExp_IT(PKA_HandleTypeDef *hpka, PKA_ModExpInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_ModExpFastMode(PKA_HandleTypeDef *hpka, PKA_ModExpFastModeInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ModExpFastMode_IT(PKA_HandleTypeDef *hpka, PKA_ModExpFastModeInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_ModExpProtectMode(PKA_HandleTypeDef *hpka, PKA_ModExpProtectModeInTypeDef *in,
                                            uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ModExpProtectMode_IT(PKA_HandleTypeDef *hpka, PKA_ModExpProtectModeInTypeDef *in);
void HAL_PKA_ModExp_GetResult(PKA_HandleTypeDef *hpka, uint8_t *pRes);
HAL_StatusTypeDef HAL_PKA_ECDSASign(PKA_HandleTypeDef *hpka, PKA_ECDSASignInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ECDSASign_IT(PKA_HandleTypeDef *hpka, PKA_ECDSASignInTypeDef *in);
void HAL_PKA_ECDSASign_GetResult(PKA_HandleTypeDef *hpka, PKA_ECDSASignOutTypeDef *out,
                                 PKA_ECDSASignOutExtParamTypeDef *outExt);
HAL_StatusTypeDef HAL_PKA_ECDSAVerif(PKA_HandleTypeDef *hpka, PKA_ECDSAVerifInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ECDSAVerif_IT(PKA_HandleTypeDef *hpka, PKA_ECDSAVerifInTypeDef *in);
uint32_t HAL_PKA_ECDSAVerif_IsValidSignature(PKA_HandleTypeDef const *const hpka);
HAL_StatusTypeDef HAL_PKA_RSACRTExp(PKA_HandleTypeDef *hpka, PKA_RSACRTExpInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_RSACRTExp_IT(PKA_HandleTypeDef *hpka, PKA_RSACRTExpInTypeDef *in);
void HAL_PKA_RSACRTExp_GetResult(PKA_HandleTypeDef *hpka, uint8_t *pRes);
HAL_StatusTypeDef HAL_PKA_PointCheck(PKA_HandleTypeDef *hpka, PKA_PointCheckInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_PointCheck_IT(PKA_HandleTypeDef *hpka, PKA_PointCheckInTypeDef *in);
uint32_t HAL_PKA_PointCheck_IsOnCurve(PKA_HandleTypeDef const *const hpka);
HAL_StatusTypeDef HAL_PKA_ECCMul(PKA_HandleTypeDef *hpka, PKA_ECCMulInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ECCMul_IT(PKA_HandleTypeDef *hpka, PKA_ECCMulInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_ECCMulEx(PKA_HandleTypeDef *hpka, PKA_ECCMulExInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ECCMulEx_IT(PKA_HandleTypeDef *hpka, PKA_ECCMulExInTypeDef *in);
void HAL_PKA_ECCMul_GetResult(PKA_HandleTypeDef *hpka, PKA_ECCMulOutTypeDef *out);
HAL_StatusTypeDef HAL_PKA_Add(PKA_HandleTypeDef *hpka, PKA_AddInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_Add_IT(PKA_HandleTypeDef *hpka, PKA_AddInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_Sub(PKA_HandleTypeDef *hpka, PKA_SubInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_Sub_IT(PKA_HandleTypeDef *hpka, PKA_SubInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_Cmp(PKA_HandleTypeDef *hpka, PKA_CmpInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_Cmp_IT(PKA_HandleTypeDef *hpka, PKA_CmpInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_Mul(PKA_HandleTypeDef *hpka, PKA_MulInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_Mul_IT(PKA_HandleTypeDef *hpka, PKA_MulInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_ModAdd(PKA_HandleTypeDef *hpka, PKA_ModAddInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ModAdd_IT(PKA_HandleTypeDef *hpka, PKA_ModAddInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_ModSub(PKA_HandleTypeDef *hpka, PKA_ModSubInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ModSub_IT(PKA_HandleTypeDef *hpka, PKA_ModSubInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_ModInv(PKA_HandleTypeDef *hpka, PKA_ModInvInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ModInv_IT(PKA_HandleTypeDef *hpka, PKA_ModInvInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_ModRed(PKA_HandleTypeDef *hpka, PKA_ModRedInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ModRed_IT(PKA_HandleTypeDef *hpka, PKA_ModRedInTypeDef *in);
HAL_StatusTypeDef HAL_PKA_MontgomeryMul(PKA_HandleTypeDef *hpka, PKA_MontgomeryMulInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_MontgomeryMul_IT(PKA_HandleTypeDef *hpka, PKA_MontgomeryMulInTypeDef *in);
void HAL_PKA_Arithmetic_GetResult(PKA_HandleTypeDef *hpka, uint32_t *pRes);
HAL_StatusTypeDef HAL_PKA_MontgomeryParam(PKA_HandleTypeDef *hpka, PKA_MontgomeryParamInTypeDef *in, uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_MontgomeryParam_IT(PKA_HandleTypeDef *hpka, PKA_MontgomeryParamInTypeDef *in);
void HAL_PKA_MontgomeryParam_GetResult(PKA_HandleTypeDef *hpka, uint32_t *pRes);
HAL_StatusTypeDef HAL_PKA_ECCDoubleBaseLadder(PKA_HandleTypeDef *hpka, PKA_ECCDoubleBaseLadderInTypeDef *in,
                                              uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ECCDoubleBaseLadder_IT(PKA_HandleTypeDef *hpka, PKA_ECCDoubleBaseLadderInTypeDef *in);
void HAL_PKA_ECCDoubleBaseLadder_GetResult(PKA_HandleTypeDef *hpka, PKA_ECCDoubleBaseLadderOutTypeDef *out);
HAL_StatusTypeDef HAL_PKA_ECCProjective2Affine(PKA_HandleTypeDef *hpka, PKA_ECCProjective2AffineInTypeDef *in,
                                               uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ECCProjective2Affine_IT(PKA_HandleTypeDef *hpka, PKA_ECCProjective2AffineInTypeDef *in);
void HAL_PKA_ECCProjective2Affine_GetResult(PKA_HandleTypeDef *hpka, PKA_ECCProjective2AffineOutTypeDef *out);
HAL_StatusTypeDef HAL_PKA_ECCCompleteAddition(PKA_HandleTypeDef *hpka, PKA_ECCCompleteAdditionInTypeDef *in,
                                              uint32_t Timeout);
HAL_StatusTypeDef HAL_PKA_ECCCompleteAddition_IT(PKA_HandleTypeDef *hpka, PKA_ECCCompleteAdditionInTypeDef *in);
void HAL_PKA_ECCCompleteAddition_GetResult(PKA_HandleTypeDef *hpka, PKA_ECCCompleteAdditionOutTypeDef *out);
HAL_StatusTypeDef HAL_PKA_Abort(PKA_HandleTypeDef *hpka);
void HAL_PKA_RAMReset(PKA_HandleTypeDef *hpka);
void HAL_PKA_OperationCpltCallback(PKA_HandleTypeDef *hpka);
void HAL_PKA_ErrorCallback(PKA_HandleTypeDef *hpka);
void HAL_PKA_IRQHandler(PKA_HandleTypeDef *hpka);
HAL_PKA_StateTypeDef HAL_PKA_GetState(const PKA_HandleTypeDef *hpka);
uint32_t HAL_PKA_GetError(const PKA_HandleTypeDef *hpka);
typedef struct
{
  uint32_t DataType;
  uint32_t KeySize;
  uint32_t *pKey;
  uint32_t *pInitVect;
  uint32_t Algorithm;
  uint32_t *Header;
  uint32_t HeaderSize;
  uint32_t *B0;
  uint32_t DataWidthUnit;
  uint32_t HeaderWidthUnit;
  uint32_t KeyIVConfigSkip;
  uint32_t KeyMode;
  uint32_t KeySelect;
  uint32_t KeyProtection;
} CRYP_ConfigTypeDef;
typedef enum
{
  HAL_CRYP_STATE_RESET = 0x00U,
  HAL_CRYP_STATE_READY = 0x01U,
  HAL_CRYP_STATE_BUSY = 0x02U,
} HAL_CRYP_STATETypeDef;
typedef struct
{
  uint32_t DataType;
  uint32_t KeySize;
  uint32_t *pKey;
  uint32_t *pInitVect;
  uint32_t Algorithm;
  uint32_t DataWidthUnit;
  uint32_t KeyIVConfigSkip;
  uint32_t KeyMode;
  uint32_t Phase;
  uint32_t KeyIVConfig;
  uint32_t CR_Reg;
  uint32_t IER_Reg;
  uint32_t IVR0_Reg;
  uint32_t IVR1_Reg;
  uint32_t IVR2_Reg;
  uint32_t IVR3_Reg;
} CRYP_ContextTypeDef;
typedef struct
{
  AES_TypeDef *Instance;
  CRYP_ConfigTypeDef Init;
  uint32_t *pCrypInBuffPtr;
  uint32_t *pCrypOutBuffPtr;
  volatile uint16_t CrypHeaderCount;
  volatile uint16_t CrypInCount;
  volatile uint16_t CrypOutCount;
  uint16_t Size;
  uint32_t Phase;
  DMA_HandleTypeDef *hdmain;
  DMA_HandleTypeDef *hdmaout;
  HAL_LockTypeDef Lock;
  volatile HAL_CRYP_STATETypeDef State;
  volatile uint32_t ErrorCode;
  uint32_t KeyIVConfig;
  uint32_t SizesSum;
} CRYP_HandleTypeDef;
HAL_StatusTypeDef HAL_CRYPEx_AESGCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, const uint32_t *pAuthTag,
                                                    uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_AESCCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, const uint32_t *pAuthTag,
                                                    uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_UnwrapKey(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_WrapKey(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint32_t *pOutput, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_EncryptSharedKey(CRYP_HandleTypeDef *hcryp, uint32_t *pKey, uint32_t *pOutput, uint32_t ID,
                                              uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_DecryptSharedKey(CRYP_HandleTypeDef *hcryp, uint32_t *pKey, uint32_t ID, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYP_Init(CRYP_HandleTypeDef *hcryp);
HAL_StatusTypeDef HAL_CRYP_DeInit(CRYP_HandleTypeDef *hcryp);
void HAL_CRYP_MspInit(CRYP_HandleTypeDef *hcryp);
void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef *hcryp);
HAL_StatusTypeDef HAL_CRYP_SetConfig(CRYP_HandleTypeDef *hcryp, CRYP_ConfigTypeDef *pConf);
HAL_StatusTypeDef HAL_CRYP_GetConfig(CRYP_HandleTypeDef *hcryp, CRYP_ConfigTypeDef *pConf);
HAL_StatusTypeDef HAL_CRYP_SaveContext(CRYP_HandleTypeDef *hcryp, CRYP_ContextTypeDef *pcont);
HAL_StatusTypeDef HAL_CRYP_RestoreContext(CRYP_HandleTypeDef *hcryp, CRYP_ContextTypeDef *pcont);
HAL_StatusTypeDef HAL_CRYP_Encrypt(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint16_t Size, uint32_t *pOutput,
                                   uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYP_Decrypt(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint16_t Size, uint32_t *pOutput,
                                   uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYP_Encrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint16_t Size, uint32_t *pOutput);
HAL_StatusTypeDef HAL_CRYP_Decrypt_IT(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint16_t Size, uint32_t *pOutput);
HAL_StatusTypeDef HAL_CRYP_Encrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint16_t Size, uint32_t *pOutput);
HAL_StatusTypeDef HAL_CRYP_Decrypt_DMA(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint16_t Size, uint32_t *pOutput);
void HAL_CRYP_IRQHandler(CRYP_HandleTypeDef *hcryp);
HAL_CRYP_STATETypeDef HAL_CRYP_GetState(const CRYP_HandleTypeDef *hcryp);
void HAL_CRYP_InCpltCallback(CRYP_HandleTypeDef *hcryp);
void HAL_CRYP_OutCpltCallback(CRYP_HandleTypeDef *hcryp);
void HAL_CRYP_ErrorCallback(CRYP_HandleTypeDef *hcryp);
uint32_t HAL_CRYP_GetError(const CRYP_HandleTypeDef *hcryp);
typedef struct
{
  HAL_LockTypeDef Lock;
  uint32_t ErrorCode;
  uint32_t ProcedureOnGoing;
  uint32_t Address;
  uint32_t Bank;
  uint32_t Sector;
  uint32_t NbSectorsToErase;
} FLASH_ProcessTypeDef;
typedef struct
{
  uint32_t TypeErase;
  uint32_t Banks;
  uint32_t Sector;
  uint32_t NbSectors;
} FLASH_EraseInitTypeDef;
typedef struct
{
  uint32_t OptionType;
  uint32_t ProductState;
  uint32_t USERType;
  uint32_t USERConfig;
  uint32_t USERConfig2;
  uint32_t Banks;
  uint32_t WRPState;
  uint64_t WRPSector;
  uint32_t BootConfig;
  uint32_t BootAddr;
  uint32_t BootLock;
  uint32_t OTPBlockLock;
  uint32_t HDPStartSector;
  uint32_t HDPEndSector;
  uint32_t EDATASize;
} FLASH_OBProgramInitTypeDef;
typedef struct
{
  uint32_t Bank;
  uint32_t BBAttributesType;
  uint32_t BBAttributes_array[(4U)];
} FLASH_BBAttributesTypeDef;
typedef struct
{
  uint32_t OperationType;
  uint32_t FlashArea;
  uint32_t Address;
} FLASH_OperationTypeDef;
typedef struct
{
  uint32_t Banks;
  uint32_t NbSectors;
} FLASH_HDPExtensionTypeDef;
typedef struct
{
  uint32_t Area;
  uint32_t Address;
  uint32_t Data;
} FLASH_EccInfoTypeDef;
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
HAL_StatusTypeDef HAL_FLASHEx_OBK_Unlock(void);
HAL_StatusTypeDef HAL_FLASHEx_OBK_Lock(void);
HAL_StatusTypeDef HAL_FLASHEx_OBK_Swap(uint32_t SwapOffset);
HAL_StatusTypeDef HAL_FLASHEx_OBK_Swap_IT(uint32_t SwapOffset);
void HAL_FLASHEx_GetOperation(FLASH_OperationTypeDef *pFlashOperation);
HAL_StatusTypeDef HAL_FLASHEx_ConfigBBAttributes(const FLASH_BBAttributesTypeDef *pBBAttributes);
void HAL_FLASHEx_GetConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes);
void HAL_FLASHEx_ConfigPrivMode(uint32_t PrivMode);
uint32_t HAL_FLASHEx_GetPrivMode(void);
HAL_StatusTypeDef HAL_FLASHEx_ConfigHDPExtension(const FLASH_HDPExtensionTypeDef *pHDPExtension);
void HAL_FLASHEx_EnableEccCorrectionInterrupt(void);
void HAL_FLASHEx_DisableEccCorrectionInterrupt(void);
void HAL_FLASHEx_GetEccInfo(FLASH_EccInfoTypeDef *pData);
void HAL_FLASHEx_ECCD_IRQHandler(void);
__attribute__((weak)) void HAL_FLASHEx_EccDetectionCallback(void);
__attribute__((weak)) void HAL_FLASHEx_EccCorrectionCallback(void);
void FLASH_Erase_Sector(uint32_t Sector, uint32_t Banks);
HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t FlashAddress, uint32_t DataAddress);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t FlashAddress, uint32_t DataAddress);
void HAL_FLASH_IRQHandler(void);
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);
HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);
HAL_StatusTypeDef HAL_FLASHEx_PUF_Launch(void);
uint32_t HAL_FLASH_GetError(void);
extern FLASH_ProcessTypeDef pFlash;
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);
typedef struct
{
  uint32_t DataType;
  uint32_t KeySize;
  uint8_t *pKey;
  uint32_t Algorithm;
} HASH_ConfigTypeDef;
typedef enum
{
  HAL_HASH_STATE_RESET = 0x00U,
  HAL_HASH_STATE_READY = 0x01U,
  HAL_HASH_STATE_BUSY = 0x02U,
  HAL_HASH_STATE_SUSPENDED = 0x03U
} HAL_HASH_StateTypeDef;
typedef enum
{
  HAL_HASH_PHASE_READY = 0x01U,
  HAL_HASH_PHASE_PROCESS = 0x02U,
  HAL_HASH_PHASE_HMAC_STEP_1 = 0x03U,
  HAL_HASH_PHASE_HMAC_STEP_2 = 0x04U,
  HAL_HASH_PHASE_HMAC_STEP_3 = 0x05U
} HAL_HASH_PhaseTypeDef;
typedef struct
{
  HASH_TypeDef *Instance;
  HASH_ConfigTypeDef Init;
  uint8_t const *pHashInBuffPtr;
  uint8_t *pHashOutBuffPtr;
  volatile uint32_t HashInCount;
  uint32_t Size;
  uint8_t *pHashKeyBuffPtr;
  HAL_HASH_PhaseTypeDef Phase;
  DMA_HandleTypeDef *hdmain;
  HAL_LockTypeDef Lock;
  volatile uint32_t ErrorCode;
  volatile HAL_HASH_StateTypeDef State;
  volatile uint32_t Accumulation;
} HASH_HandleTypeDef;
HAL_StatusTypeDef HAL_HASH_Init(HASH_HandleTypeDef *hhash);
HAL_StatusTypeDef HAL_HASH_DeInit(HASH_HandleTypeDef *hhash);
void HAL_HASH_MspInit(HASH_HandleTypeDef *hhash);
void HAL_HASH_MspDeInit(HASH_HandleTypeDef *hhash);
HAL_StatusTypeDef HAL_HASH_GetConfig(HASH_HandleTypeDef *hhash, HASH_ConfigTypeDef *pConf);
HAL_StatusTypeDef HAL_HASH_SetConfig(HASH_HandleTypeDef *hhash, const HASH_ConfigTypeDef *pConf);
HAL_StatusTypeDef HAL_HASH_ProcessSuspend(HASH_HandleTypeDef *hhash);
void HAL_HASH_Resume(HASH_HandleTypeDef *hhash, uint8_t *pMemBuffer);
void HAL_HASH_Suspend(HASH_HandleTypeDef *hhash, uint8_t *pMemBuffer);
HAL_StatusTypeDef HAL_HASH_Start(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                 uint8_t *const pOutBuffer,
                                 uint32_t Timeout);
HAL_StatusTypeDef HAL_HASH_Start_IT(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                    uint8_t *const pOutBuffer);
HAL_StatusTypeDef HAL_HASH_Start_DMA(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                     uint8_t *const pOutBuffer);
HAL_StatusTypeDef HAL_HASH_Accumulate(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                      uint32_t Timeout);
HAL_StatusTypeDef HAL_HASH_AccumulateLast(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                          uint8_t *const pOutBuffer,
                                          uint32_t Timeout);
HAL_StatusTypeDef HAL_HASH_AccumulateLast_IT(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                             uint8_t *const pOutBuffer);
HAL_StatusTypeDef HAL_HASH_Accumulate_IT(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size);
HAL_StatusTypeDef HAL_HASH_HMAC_Start(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                      uint8_t *const pOutBuffer,
                                      uint32_t Timeout);
HAL_StatusTypeDef HAL_HASH_HMAC_Start_DMA(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                          uint8_t *const pOutBuffer);
HAL_StatusTypeDef HAL_HASH_HMAC_Start_IT(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                         uint8_t *const pOutBuffer);
HAL_StatusTypeDef HAL_HASH_HMAC_Accumulate(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_HASH_HMAC_AccumulateLast(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size,
                                               uint8_t *const pOutBuffer, uint32_t Timeout);
HAL_StatusTypeDef HAL_HASH_HMAC_Accumulate_IT(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer, uint32_t Size);
HAL_StatusTypeDef HAL_HASH_HMAC_AccumulateLast_IT(HASH_HandleTypeDef *hhash, const uint8_t *const pInBuffer,
                                                  uint32_t Size, uint8_t *const pOutBuffer);
void HAL_HASH_IRQHandler(HASH_HandleTypeDef *hhash);
void HAL_HASH_InCpltCallback(HASH_HandleTypeDef *hhash);
void HAL_HASH_DgstCpltCallback(HASH_HandleTypeDef *hhash);
void HAL_HASH_ErrorCallback(HASH_HandleTypeDef *hhash);
HAL_HASH_StateTypeDef HAL_HASH_GetState(const HASH_HandleTypeDef *hhash);
uint32_t HAL_HASH_GetError(const HASH_HandleTypeDef *hhash);
typedef struct
{
  uint32_t PVDLevel;
  uint32_t Mode;
} PWR_PVDTypeDef;
typedef struct
{
  uint32_t AVDLevel;
  uint32_t Mode;
} PWREx_AVDTypeDef;
typedef struct
{
  uint32_t WakeUpPin;
  uint32_t PinPolarity;
  uint32_t PinPull;
} PWREx_WakeupPinTypeDef;
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource);
uint32_t HAL_PWREx_GetSupplyConfig(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
uint32_t HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlStopModeVoltageScaling(uint32_t VoltageScaling);
uint32_t HAL_PWREx_GetStopModeVoltageRange(void);
void HAL_PWREx_ConfigAVD(const PWREx_AVDTypeDef *sConfigAVD);
void HAL_PWREx_EnableAVD(void);
void HAL_PWREx_DisableAVD(void);
void HAL_PWREx_EnableUSBVoltageDetector(void);
void HAL_PWREx_DisableUSBVoltageDetector(void);
void HAL_PWREx_EnableVddUSB(void);
void HAL_PWREx_DisableVddUSB(void);
void HAL_PWREx_EnableUSBOTGHSPhy(void);
void HAL_PWREx_DisableUSBOTGHSPhy(void);
void HAL_PWREx_EnableMonitoring(void);
void HAL_PWREx_DisableMonitoring(void);
void HAL_PWREx_EnableUCPDStandbyMode(void);
void HAL_PWREx_DisableUCPDStandbyMode(void);
void HAL_PWREx_EnableUCPDDeadBattery(void);
void HAL_PWREx_DisableUCPDDeadBattery(void);
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorValue);
void HAL_PWREx_DisableBatteryCharging(void);
void HAL_PWREx_EnableAnalogBooster(void);
void HAL_PWREx_DisableAnalogBooster(void);
void HAL_PWREx_PVD_AVD_IRQHandler(void);
void HAL_PWREx_PVD_AVD_Rising_Callback(void);
void HAL_PWREx_PVD_AVD_Falling_Callback(void);
void HAL_PWREx_EnableWakeUpPin(const PWREx_WakeupPinTypeDef *sPinParams);
void HAL_PWREx_DisableWakeUpPin(uint32_t WakeUpPinx);
void HAL_PWREx_EnableFlashPowerDown(void);
void HAL_PWREx_DisableFlashPowerDown(void);
void HAL_PWREx_EnableMemoryShutOff(uint32_t MemoryBlock);
void HAL_PWREx_DisableMemoryShutOff(uint32_t MemoryBlock);
HAL_StatusTypeDef HAL_PWREx_EnableBkupRAMRetention(void);
void HAL_PWREx_DisableBkupRAMRetention(void);
void HAL_PWREx_EnableStandbyIORetention(void);
void HAL_PWREx_DisableStandbyIORetention(void);
void HAL_PWREx_EnableStandbyJTAGIORetention(void);
void HAL_PWREx_DisableStandbyJTAGIORetention(void);
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);
HAL_StatusTypeDef HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinPolarity);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSTANDBYMode(void);
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);
void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);
void HAL_PWR_ConfigAttributes(uint32_t Item, uint32_t Attributes);
HAL_StatusTypeDef HAL_PWR_GetConfigAttributes(uint32_t Item, uint32_t *pAttributes);
typedef struct
{
  uint32_t ClockErrorDetection;
} RNG_InitTypeDef;
typedef enum
{
  HAL_RNG_STATE_RESET = 0x00U,
  HAL_RNG_STATE_READY = 0x01U,
  HAL_RNG_STATE_BUSY = 0x02U,
  HAL_RNG_STATE_TIMEOUT = 0x03U,
  HAL_RNG_STATE_ERROR = 0x04U
} HAL_RNG_StateTypeDef;
typedef struct
{
  RNG_TypeDef *Instance;
  RNG_InitTypeDef Init;
  HAL_LockTypeDef Lock;
  volatile HAL_RNG_StateTypeDef State;
  volatile uint32_t ErrorCode;
  uint32_t RandomNumber;
} RNG_HandleTypeDef;
typedef struct
{
  uint32_t Config1;
  uint32_t Config2;
  uint32_t Config3;
  uint32_t ClockDivider;
  uint32_t NistCompliance;
  uint32_t AutoReset;
  uint32_t HealthTest;
} RNG_ConfigTypeDef;
HAL_StatusTypeDef HAL_RNGEx_SetConfig(RNG_HandleTypeDef *hrng, const RNG_ConfigTypeDef *pConf);
HAL_StatusTypeDef HAL_RNGEx_GetConfig(RNG_HandleTypeDef *hrng, RNG_ConfigTypeDef *pConf);
HAL_StatusTypeDef HAL_RNGEx_LockConfig(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNGEx_RecoverSeedError(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNG_Init(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNG_DeInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng);
void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber(RNG_HandleTypeDef *hrng, uint32_t *random32bit);
HAL_StatusTypeDef HAL_RNG_GenerateRandomNumber_IT(RNG_HandleTypeDef *hrng);
uint32_t HAL_RNG_ReadLastRandomNumber(const RNG_HandleTypeDef *hrng);
void HAL_RNG_IRQHandler(RNG_HandleTypeDef *hrng);
void HAL_RNG_ErrorCallback(RNG_HandleTypeDef *hrng);
void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *hrng, uint32_t random32bit);
HAL_RNG_StateTypeDef HAL_RNG_GetState(const RNG_HandleTypeDef *hrng);
uint32_t HAL_RNG_GetError(const RNG_HandleTypeDef *hrng);
HAL_StatusTypeDef RNG_RecoverSeedError(RNG_HandleTypeDef *hrng);
typedef enum
{
  HAL_RTC_STATE_RESET = 0x00U,
  HAL_RTC_STATE_READY = 0x01U,
  HAL_RTC_STATE_BUSY = 0x02U,
  HAL_RTC_STATE_TIMEOUT = 0x03U,
  HAL_RTC_STATE_ERROR = 0x04U
} HAL_RTCStateTypeDef;
typedef struct
{
  uint32_t HourFormat;
  uint32_t AsynchPrediv;
  uint32_t SynchPrediv;
  uint32_t OutPut;
  uint32_t OutPutRemap;
  uint32_t OutPutPolarity;
  uint32_t OutPutType;
  uint32_t OutPutPullUp;
  uint32_t BinMode;
  uint32_t BinMixBcdU;
} RTC_InitTypeDef;
typedef struct
{
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
  uint8_t TimeFormat;
  uint32_t SubSeconds;
  uint32_t SecondFraction;
  uint32_t DayLightSaving;
  uint32_t StoreOperation;
} RTC_TimeTypeDef;
typedef struct
{
  uint8_t WeekDay;
  uint8_t Month;
  uint8_t Date;
  uint8_t Year;
} RTC_DateTypeDef;
typedef struct
{
  RTC_TimeTypeDef AlarmTime;
  uint32_t AlarmMask;
  uint32_t AlarmSubSecondMask;
  uint32_t BinaryAutoClr;
  uint32_t AlarmDateWeekDaySel;
  uint8_t AlarmDateWeekDay;
  uint32_t FlagAutoClr;
  uint32_t Alarm;
} RTC_AlarmTypeDef;
typedef struct
{
  RTC_TypeDef *Instance;
  RTC_InitTypeDef Init;
  HAL_LockTypeDef Lock;
  volatile HAL_RTCStateTypeDef State;
} RTC_HandleTypeDef;
typedef struct
{
  uint32_t Tamper;
  uint32_t Trigger;
  uint32_t NoErase;
  uint32_t MaskFlag;
  uint32_t Filter;
  uint32_t SamplingFrequency;
  uint32_t PrechargeDuration;
  uint32_t TamperPullUp;
  uint32_t TimeStampOnTamperDetection;
} RTC_TamperTypeDef;
typedef struct
{
  uint32_t Enable;
  uint32_t Interrupt;
  uint32_t Output;
  uint32_t NoErase;
  uint32_t MaskFlag;
} RTC_ATampInputTypeDef;
typedef struct
{
  uint32_t ActiveFilter;
  uint32_t ActiveAsyncPrescaler;
  uint32_t TimeStampOnTamperDetection;
  uint32_t ActiveOutputChangePeriod;
  uint32_t Seed[4U];
  RTC_ATampInputTypeDef TampInput[8U];
} RTC_ActiveTampersTypeDef;
typedef struct
{
  uint32_t IntTamper;
  uint32_t TimeStampOnTamperDetection;
  uint32_t NoErase;
} RTC_InternalTamperTypeDef;
typedef struct
{
  uint32_t rtcSecureFull;
  uint32_t rtcNonSecureFeatures;
  uint32_t tampSecureFull;
  uint32_t backupRegisterStartZone2;
  uint32_t backupRegisterStartZone3;
  uint32_t MonotonicCounterSecure;
} RTC_SecureStateTypeDef;
typedef struct
{
  uint32_t rtcPrivilegeFull;
  uint32_t rtcPrivilegeFeatures;
  uint32_t tampPrivilegeFull;
  uint32_t backupRegisterPrivZone;
  uint32_t backupRegisterStartZone2;
  uint32_t backupRegisterStartZone3;
  uint32_t MonotonicCounterPrivilege;
} RTC_PrivilegeStateTypeDef;
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(const RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTimeStamp,
                                         RTC_DateTypeDef *sTimeStampDate, uint32_t Format);
void HAL_RTCEx_TimeStampIRQHandler(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(const RTC_HandleTypeDef *hrtc, uint32_t Timeout);
void HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock);
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock,
                                              uint32_t WakeUpAutoClr);
HAL_StatusTypeDef HAL_RTCEx_DeactivateWakeUpTimer(RTC_HandleTypeDef *hrtc);
uint32_t HAL_RTCEx_GetWakeUpTimer(const RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForWakeUpTimerEvent(const RTC_HandleTypeDef *hrtc, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod,
                                           uint32_t SmoothCalibPlusPulses, uint32_t SmoothCalibMinusPulsesValue);
HAL_StatusTypeDef HAL_RTCEx_SetLowPowerCalib(RTC_HandleTypeDef *hrtc, uint32_t LowPowerCalib);
HAL_StatusTypeDef HAL_RTCEx_SetSynchroShift(RTC_HandleTypeDef *hrtc, uint32_t ShiftAdd1S, uint32_t ShiftSubFS);
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef *hrtc, uint32_t CalibOutput);
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_EnableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DisableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterIncrement(const RTC_HandleTypeDef *hrtc, uint32_t Instance);
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterGet(const RTC_HandleTypeDef *hrtc, uint32_t Instance, uint32_t *pValue);
HAL_StatusTypeDef HAL_RTCEx_SetSSRU_IT(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateSSRU(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_SSRUIRQHandler(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_SSRUEventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(const RTC_HandleTypeDef *hrtc, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_SetTamper(const RTC_HandleTypeDef *hrtc, const RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_SetActiveTampers(RTC_HandleTypeDef *hrtc, const RTC_ActiveTampersTypeDef *sAllTamper);
HAL_StatusTypeDef HAL_RTCEx_SetActiveSeed(RTC_HandleTypeDef *hrtc, const uint32_t *pSeed);
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(const RTC_HandleTypeDef *hrtc, const RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(const RTC_HandleTypeDef *hrtc, uint32_t Tamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateActiveTampers(const RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTamperEvent(const RTC_HandleTypeDef *hrtc, uint32_t Tamper, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper(const RTC_HandleTypeDef *hrtc,
                                              const RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper_IT(const RTC_HandleTypeDef *hrtc,
                                                 const RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTamper(const RTC_HandleTypeDef *hrtc, uint32_t IntTamper);
HAL_StatusTypeDef HAL_RTCEx_PollForInternalTamperEvent(const RTC_HandleTypeDef *hrtc, uint32_t IntTamper,
                                                       uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_LockBootHardwareKey(const RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_TamperIRQHandler(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper3EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper4EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper5EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper6EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper7EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_Tamper8EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper1EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper2EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper3EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper4EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper5EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper6EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper7EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper8EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper9EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper11EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper12EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper13EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_InternalTamper15EventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_BKUPWrite(const RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data);
uint32_t HAL_RTCEx_BKUPRead(const RTC_HandleTypeDef *hrtc, uint32_t BackupRegister);
void HAL_RTCEx_BKUPErase(const RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_BKUPBlock(const RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_BKUPUnblock(const RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_ConfigEraseDeviceSecrets(const RTC_HandleTypeDef *hrtc, uint32_t DeviceSecretConf);
HAL_StatusTypeDef HAL_RTCEx_SecureModeGet(const RTC_HandleTypeDef *hrtc, RTC_SecureStateTypeDef *secureState);
HAL_StatusTypeDef HAL_RTCEx_PrivilegeModeSet(const RTC_HandleTypeDef *hrtc,
                                             const RTC_PrivilegeStateTypeDef *privilegeState);
HAL_StatusTypeDef HAL_RTCEx_PrivilegeModeGet(const RTC_HandleTypeDef *hrtc, RTC_PrivilegeStateTypeDef *privilegeState);
void HAL_RTCEx_EnableRemapRtcOut2(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_DisableRemapRtcOut2(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_Init(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc);
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc);
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_GetTime(const RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_GetDate(const RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format);
void HAL_RTC_DST_Add1Hour(const RTC_HandleTypeDef *hrtc);
void HAL_RTC_DST_Sub1Hour(const RTC_HandleTypeDef *hrtc);
void HAL_RTC_DST_SetStoreOperation(const RTC_HandleTypeDef *hrtc);
void HAL_RTC_DST_ClearStoreOperation(const RTC_HandleTypeDef *hrtc);
uint32_t HAL_RTC_DST_ReadStoreOperation(const RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_SetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_SetAlarm_IT(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_DeactivateAlarm(RTC_HandleTypeDef *hrtc, uint32_t Alarm);
HAL_StatusTypeDef HAL_RTC_GetAlarm(const RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Alarm,
                                   uint32_t Format);
void HAL_RTC_AlarmIRQHandler(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_PollForAlarmAEvent(const RTC_HandleTypeDef *hrtc, uint32_t Timeout);
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_WaitForSynchro(RTC_HandleTypeDef *hrtc);
HAL_RTCStateTypeDef HAL_RTC_GetState(const RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef *hrtc);
uint8_t RTC_ByteToBcd2(uint8_t Value);
uint8_t RTC_Bcd2ToByte(uint8_t Value);
typedef struct
{
  uint32_t BaudRate;
  uint32_t WordLength;
  uint32_t StopBits;
  uint32_t Parity;
  uint32_t Mode;
  uint32_t HwFlowCtl;
  uint32_t OverSampling;
  uint32_t OneBitSampling;
  uint32_t ClockPrescaler;
} UART_InitTypeDef;
typedef struct
{
  uint32_t AdvFeatureInit;
  uint32_t TxPinLevelInvert;
  uint32_t RxPinLevelInvert;
  uint32_t DataInvert;
  uint32_t Swap;
  uint32_t OverrunDisable;
  uint32_t DMADisableonRxError;
  uint32_t AutoBaudRateEnable;
  uint32_t AutoBaudRateMode;
  uint32_t MSBFirst;
} UART_AdvFeatureInitTypeDef;
typedef uint32_t HAL_UART_StateTypeDef;
typedef enum
{
  UART_CLOCKSOURCE_PCLK1 = 0x00U,
  UART_CLOCKSOURCE_PLL2Q = 0x01U,
  UART_CLOCKSOURCE_PLL3Q = 0x02U,
  UART_CLOCKSOURCE_HSI = 0x04U,
  UART_CLOCKSOURCE_CSI = 0x08U,
  UART_CLOCKSOURCE_LSE = 0x10U,
  UART_CLOCKSOURCE_UNDEFINED = 0x20U
} UART_ClockSourceTypeDef;
typedef uint32_t HAL_UART_RxTypeTypeDef;
typedef uint32_t HAL_UART_RxEventTypeTypeDef;
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef *Instance;
  UART_InitTypeDef Init;
  UART_AdvFeatureInitTypeDef AdvancedInit;
  const uint8_t *pTxBuffPtr;
  uint16_t TxXferSize;
  volatile uint16_t TxXferCount;
  uint8_t *pRxBuffPtr;
  uint16_t RxXferSize;
  volatile uint16_t RxXferCount;
  uint16_t Mask;
  uint32_t FifoMode;
  uint16_t NbRxDataToProcess;
  uint16_t NbTxDataToProcess;
  volatile HAL_UART_RxTypeTypeDef ReceptionType;
  volatile HAL_UART_RxEventTypeTypeDef RxEventType;
  void (*RxISR)(struct __UART_HandleTypeDef *huart);
  void (*TxISR)(struct __UART_HandleTypeDef *huart);
  DMA_HandleTypeDef *hdmatx;
  DMA_HandleTypeDef *hdmarx;
  HAL_LockTypeDef Lock;
  volatile HAL_UART_StateTypeDef gState;
  volatile HAL_UART_StateTypeDef RxState;
  volatile uint32_t ErrorCode;
} UART_HandleTypeDef;
typedef struct
{
  uint32_t WakeUpEvent;
  uint16_t AddressLength;
  uint8_t Address;
} UART_WakeUpTypeDef;
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t Polarity, uint32_t AssertionTime,
                                   uint32_t DeassertionTime);
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart);
void HAL_UARTEx_RxFifoFullCallback(UART_HandleTypeDef *huart);
void HAL_UARTEx_TxFifoEmptyCallback(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_StopModeWakeUpSourceConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection);
HAL_StatusTypeDef HAL_UARTEx_EnableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(UART_HandleTypeDef *huart, uint32_t AddressLength);
HAL_StatusTypeDef HAL_UARTEx_EnableFifoMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableFifoMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_SetTxFifoThreshold(UART_HandleTypeDef *huart, uint32_t Threshold);
HAL_StatusTypeDef HAL_UARTEx_SetRxFifoThreshold(UART_HandleTypeDef *huart, uint32_t Threshold);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_UART_RxEventTypeTypeDef HAL_UARTEx_GetRxEventType(const UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart);
void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
void HAL_UART_ReceiverTimeout_Config(UART_HandleTypeDef *huart, uint32_t TimeoutValue);
HAL_StatusTypeDef HAL_UART_EnableReceiverTimeout(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DisableReceiverTimeout(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_EnableMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_DisableMuteMode(UART_HandleTypeDef *huart);
void HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);
HAL_UART_StateTypeDef HAL_UART_GetState(const UART_HandleTypeDef *huart);
uint32_t HAL_UART_GetError(const UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_SetConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_CheckIdleState(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status,
                                              uint32_t Tickstart, uint32_t Timeout);
void UART_AdvFeatureConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_Start_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef UART_Start_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
extern const uint16_t UARTPrescTable[12];
typedef enum
{
  HAL_EXTI_COMMON_CB_ID = 0x00U,
  HAL_EXTI_RISING_CB_ID = 0x01U,
  HAL_EXTI_FALLING_CB_ID = 0x02U,
} EXTI_CallbackIDTypeDef;
typedef struct
{
  uint32_t Line;
  void (* RisingCallback)(void);
  void (* FallingCallback)(void);
} EXTI_HandleTypeDef;
typedef struct
{
  uint32_t Line;
  uint32_t Mode;
  uint32_t Trigger;
  uint32_t GPIOSel;
} EXTI_ConfigTypeDef;
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, const EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(const EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(const EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID,
                                            void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);
void HAL_EXTI_IRQHandler(const EXTI_HandleTypeDef *hexti);
uint32_t HAL_EXTI_GetPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_ClearPending(const EXTI_HandleTypeDef *hexti, uint32_t Edge);
void HAL_EXTI_GenerateSWI(const EXTI_HandleTypeDef *hexti);
void HAL_EXTI_ConfigLineAttributes(uint32_t ExtiLine, uint32_t LineAttributes);
HAL_StatusTypeDef HAL_EXTI_GetConfigLineAttributes(uint32_t ExtiLine, uint32_t *pLineAttributes);
typedef enum
{
  HAL_RAMCFG_STATE_RESET = 0x00U,
  HAL_RAMCFG_STATE_READY = 0x01U,
  HAL_RAMCFG_STATE_BUSY = 0x02U,
  HAL_RAMCFG_STATE_ERROR = 0x03U,
} HAL_RAMCFG_StateTypeDef;
typedef struct
{
  RAMCFG_TypeDef *Instance;
  volatile HAL_RAMCFG_StateTypeDef State;
  volatile uint32_t ErrorCode;
} RAMCFG_HandleTypeDef;
HAL_StatusTypeDef HAL_RAMCFG_Init(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_DeInit(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_MspInit(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_MspDeInit(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_StartECC(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_StopECC(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_EnableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications);
HAL_StatusTypeDef HAL_RAMCFG_DisableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications);
uint32_t HAL_RAMCFG_IsECCSingleErrorDetected(const RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_IsECCDoubleErrorDetected(const RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_GetSingleErrorAddress(const RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_GetDoubleErrorAddress(const RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_EnableWriteProtection(RAMCFG_HandleTypeDef *hramcfg, uint32_t StartPage, uint32_t NbPage);
HAL_StatusTypeDef HAL_RAMCFG_Erase(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_IRQHandler(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_DetectSingleErrorCallback(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_DetectDoubleErrorCallback(RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_GetError(const RAMCFG_HandleTypeDef *hramcfg);
HAL_RAMCFG_StateTypeDef HAL_RAMCFG_GetState(const RAMCFG_HandleTypeDef *hramcfg);
typedef enum
{
  HAL_TICK_FREQ_10HZ = 100U,
  HAL_TICK_FREQ_100HZ = 10U,
  HAL_TICK_FREQ_1KHZ = 1U,
  HAL_TICK_FREQ_DEFAULT = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
extern volatile uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);
void HAL_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling);
void HAL_VREFBUF_HighImpedanceConfig(uint32_t Mode);
void HAL_VREFBUF_TrimmingConfig(uint32_t TrimmingValue);
HAL_StatusTypeDef HAL_EnableVREFBUF(void);
void HAL_DisableVREFBUF(void);
void HAL_SBS_ETHInterfaceSelect(uint32_t SBS_ETHInterface);
void HAL_SBS_EnableVddIO1CompensationCell(void);
void HAL_SBS_DisableVddIO1CompensationCell(void);
void HAL_SBS_EnableVddIO2CompensationCell(void);
void HAL_SBS_DisableVddIO2CompensationCell(void);
void HAL_SBS_VDDCompensationCodeSelect(uint32_t SBS_CompCode);
void HAL_SBS_VDDIOCompensationCodeSelect(uint32_t SBS_CompCode);
uint32_t HAL_SBS_GetVddIO1CompensationCellReadyFlag(void);
uint32_t HAL_SBS_GetVddIO2CompensationCellReadyFlag(void);
void HAL_SBS_VDDCompensationCodeConfig(uint32_t SBS_PMOSCode, uint32_t SBS_NMOSCode);
void HAL_SBS_VDDIOCompensationCodeConfig(uint32_t SBS_PMOSCode, uint32_t SBS_NMOSCode);
uint32_t HAL_SBS_GetNMOSVddCompensationValue(void);
uint32_t HAL_SBS_GetPMOSVddCompensationValue(void);
uint32_t HAL_SBS_GetNMOSVddIO2CompensationValue(void);
uint32_t HAL_SBS_GetPMOSVddIO2CompensationValue(void);
void HAL_SBS_FLASH_EnableECCNMI(void);
void HAL_SBS_FLASH_DisableECCNMI(void);
uint32_t HAL_SBS_FLASH_ECCNMI_IsDisabled(void);
void HAL_SBS_SetOTGPHYDisconnectThreshold(uint32_t DisconnectThreshold);
uint32_t HAL_SBS_GetOTGPHYDisconnectThreshold(void);
void HAL_SBS_SetOTGPHYSquelchThreshold(uint32_t SquelchThreshold);
uint32_t HAL_SBS_GetOTGPHYSquelchThreshold(void);
void HAL_SBS_SetOTGPHYPreemphasisCurrent(uint32_t PreemphasisCurrent);
uint32_t HAL_SBS_GetOTGPHYPreemphasisCurrent(void);
void HAL_SBS_IncrementHDPLValue(void);
uint32_t HAL_SBS_GetHDPLValue(void);
void HAL_SBS_EPOCHSelection(uint32_t Epoch_Selection);
uint32_t HAL_SBS_GetEPOCHSelection(void);
void HAL_SBS_SetOBKHDPL(uint32_t OBKHDPL_Value);
uint32_t HAL_SBS_GetOBKHDPL(void);
void HAL_SBS_OpenAccessPort(void);
void HAL_SBS_OpenDebug(void);
HAL_StatusTypeDef HAL_SBS_ConfigDebugLevel(uint32_t Level);
uint32_t HAL_SBS_GetDebugLevel(void);
void HAL_SBS_LockDebugConfig(void);
void HAL_SBS_ConfigDebugSecurity(uint32_t Security);
uint32_t HAL_SBS_GetDebugSecurity(void);
void HAL_SBS_Lock(uint32_t Item);
HAL_StatusTypeDef HAL_SBS_GetLock(uint32_t *pItem);
enum image_attributes
{
  RE_FLASH_AREA_BL2_OFFSET = (0x0000),
  RE_FLASH_AREA_BL2_SIZE = (0x18000),
  RE_FLASH_AREA_SCRATCH_OFFSET = ((0x18000)),
  RE_FLASH_AREA_SCRATCH_SIZE = (0x10000),
  RE_IMAGE_FLASH_SECURE_IMAGE_SIZE = ((0x08000)),
  RE_IMAGE_NON_SECURE_IMAGE_SIZE = ((0x0)),
  RE_IMAGE_FLASH_NON_SECURE_IMAGE_SIZE = ((0x0)+(0x08000)),
  RE_CODE_IMAGE_ASSEMBLY = (0x1),
  RE_ADDRESS_SECURE_START = ((((0x0C000000)) + ((((((0x10000)+(0x18000)) + (0x0))) + (0x400))))) - (0x400),
  RE_ADDRESS_NON_SECURE_START = ((((0x08000000)) + ((((((0x10000)+(0x18000)) + (0x0)) + (0x08000)) + (0x400))))) - (0x400),
  RE_IMAGE_FLASH_ADDRESS_SECURE = ((0x08000000)+(((0x10000)+(0x18000)) + (0x0))),
  RE_IMAGE_FLASH_ADDRESS_SECURE_MAGIC_INSTALL_REQ = ((0x08000000)+(((0x10000)+(0x18000)) + (0x0))+(((0x08000)+(0x0)))-0x10),
  RE_APP_IMAGE_NUMBER = (0x1),
  RE_EXTERNAL_FLASH_ENABLE = (0x0),
  RE_CODE_START_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_NON_SECURE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_SECURE_UPDATE = ((0x08000000)+(((0x10000)+(0x18000)) + (0x0) + (((0x08000)+(0x0))) + (0x0) + (0x0))),
  RE_IMAGE_FLASH_SECURE_UPDATE_MAGIC_INSTALL_REQ = ((0x08000000)+(((0x10000)+(0x18000)) + (0x0) + (((0x08000)+(0x0))) + (0x0) + (0x0))+(((0x08000)+(0x0)))-0x10),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE = (0x0),
  RE_IMAGE_FLASH_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (0x0),
  RE_PRIMARY_ONLY = (0x0),
  RE_S_DATA_IMAGE_NUMBER = (0x0),
  RE_IMAGE_FLASH_ADDRESS_DATA_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_DATA_SECURE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE = (0x0),
  RE_IMAGE_FLASH_DATA_SECURE_UPDATE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_SECURE_DATA_IMAGE_SIZE = (0x0),
  RE_NS_DATA_IMAGE_NUMBER = (0x0),
  RE_IMAGE_FLASH_ADDRESS_DATA_NON_SECURE = (0x0),
  RE_IMAGE_FLASH_ADDRESS_DATA_NON_SECURE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE = (0x0),
  RE_IMAGE_FLASH_DATA_NON_SECURE_UPDATE_MAGIC_INSTALL_REQ = (0x0),
  RE_IMAGE_FLASH_NON_SECURE_DATA_IMAGE_SIZE = (0x0),
  RE_BL2_BOOT_ADDRESS = ((((((0x0C000000)) + ((0x0000)))))),
  RE_BL2_SEC1_END = ((((0x10000)+(0x18000)) + (0x0))+(0x08000)-0x1),
  RE_BL2_SEC2_START = ((0x100000)-0x1),
  RE_BL2_SEC2_END = (0x0),
  RE_BL2_WRP_START = ((0x0000)),
  RE_BL2_HDP_START = 0x0,
  RE_BL2_HDP_END = ((0x0000)+(0x18000)+(0x10000)-0x1),
  RE_BL2_WRP_END = ((0x0000)+(0x18000)-0x1),
  RE_AREA_0_OFFSET = (((0x10000)+(0x18000)) + (0x0)),
  RE_AREA_0_SIZE = (((0x08000)+(0x0))),
  RE_AREA_1_OFFSET = (0x0),
  RE_AREA_1_SIZE = (0x0),
  RE_AREA_2_OFFSET = (((0x10000)+(0x18000)) + (0x0) + (((0x08000)+(0x0))) + (0x0) + (0x0)),
  RE_AREA_2_SIZE = (((0x08000)+(0x0))),
  RE_AREA_3_OFFSET = (0x0),
  RE_AREA_3_SIZE = (0x0),
  RE_AREA_4_OFFSET = (0x0),
  RE_AREA_4_SIZE = (0x0),
  RE_AREA_5_OFFSET = (0x0),
  RE_AREA_5_SIZE = (0x0),
  RE_AREA_6_OFFSET = (0x0),
  RE_AREA_6_SIZE = (0x0),
  RE_AREA_7_OFFSET = (0x0),
  RE_AREA_7_SIZE = (0x0),
  RE_S_NS_PARTITION_SIZE = ((0x08000)+(0x0)),
  RE_FLASH_B_SIZE = (0x100000),
  RE_CRYPTO_SCHEME = 0x2,
  RE_ENCRYPTION = (0x1),
  RE_OVER_WRITE = (0x0),
  RE_CMSE_VENEER_REGION_SIZE = (0x2000),
  RE_OEMIROT_APPLI_FULL_SECURE = (0x1),
  RE_OEMUROT_ENABLE = (0x0),
  RE_FLASH_PAGE_NBR = (0x7F)
};
