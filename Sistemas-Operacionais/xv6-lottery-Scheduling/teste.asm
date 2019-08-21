
_teste: formato do arquivo elf32-i386


Desmontagem da seção .text:

00000000 <main>:
#include "types.h"
#include "stat.h"
#include "user.h"
#define OUTPUT_STREAM 1
int main(void) {
   0:	8d 4c 24 04          	lea    0x4(%esp),%ecx
   4:	83 e4 f0             	and    $0xfffffff0,%esp
   7:	ff 71 fc             	pushl  -0x4(%ecx)
   a:	55                   	push   %ebp
   b:	89 e5                	mov    %esp,%ebp
   d:	53                   	push   %ebx
   e:	51                   	push   %ecx
  int pid;
  pid = fork();
   f:	e8 96 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  14:	85 c0                	test   %eax,%eax
  16:	75 3d                	jne    55 <main+0x55>
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (pid) pid = fork();
  if (!pid) { // Se for o filho
    int i = 0;
    printf(OUTPUT_STREAM, "Filho: %d\n", getpid());
  18:	e8 15 04 00 00       	call   432 <getpid>
  1d:	83 ec 04             	sub    $0x4,%esp
  20:	bb 9f 86 01 00       	mov    $0x1869f,%ebx
  25:	50                   	push   %eax
  26:	68 58 08 00 00       	push   $0x858
  2b:	6a 01                	push   $0x1
  2d:	e8 ce 04 00 00       	call   500 <printf>
  32:	83 c4 10             	add    $0x10,%esp
  35:	8d 76 00             	lea    0x0(%esi),%esi
    while(i++ < 99999) {
      int j = 0;
      while(j++ < 1) {
        int b = getpid() * 5 / 3 + 7;
  38:	e8 f5 03 00 00       	call   432 <getpid>
        b += b + getpid();
  3d:	e8 f0 03 00 00       	call   432 <getpid>
    while(i++ < 99999) {
  42:	83 eb 01             	sub    $0x1,%ebx
  45:	75 f1                	jne    38 <main+0x38>
  47:	89 f6                	mov    %esi,%esi
  49:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
    wait();
    printf(OUTPUT_STREAM, "filho terminou.\n");
  } else {
    printf(OUTPUT_STREAM, "Erro\n");
  }
  exit();
  50:	e8 5d 03 00 00       	call   3b2 <exit>
  if (pid) pid = fork();
  55:	e8 50 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  5a:	85 c0                	test   %eax,%eax
  5c:	74 ba                	je     18 <main+0x18>
  5e:	e8 47 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  63:	85 c0                	test   %eax,%eax
  65:	74 b1                	je     18 <main+0x18>
  67:	e8 3e 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  6c:	85 c0                	test   %eax,%eax
  6e:	74 a8                	je     18 <main+0x18>
  70:	e8 35 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  75:	85 c0                	test   %eax,%eax
  77:	74 9f                	je     18 <main+0x18>
  79:	e8 2c 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  7e:	85 c0                	test   %eax,%eax
  80:	74 96                	je     18 <main+0x18>
  82:	e8 23 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  87:	85 c0                	test   %eax,%eax
  89:	74 8d                	je     18 <main+0x18>
  8b:	e8 1a 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  90:	85 c0                	test   %eax,%eax
  92:	74 84                	je     18 <main+0x18>
  94:	e8 11 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  99:	85 c0                	test   %eax,%eax
  9b:	0f 84 77 ff ff ff    	je     18 <main+0x18>
  a1:	e8 04 03 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  a6:	85 c0                	test   %eax,%eax
  a8:	0f 84 6a ff ff ff    	je     18 <main+0x18>
  ae:	e8 f7 02 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  b3:	85 c0                	test   %eax,%eax
  b5:	0f 84 5d ff ff ff    	je     18 <main+0x18>
  bb:	e8 ea 02 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  c0:	85 c0                	test   %eax,%eax
  c2:	0f 84 50 ff ff ff    	je     18 <main+0x18>
  c8:	e8 dd 02 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  cd:	85 c0                	test   %eax,%eax
  cf:	0f 84 43 ff ff ff    	je     18 <main+0x18>
  d5:	e8 d0 02 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  da:	85 c0                	test   %eax,%eax
  dc:	0f 84 36 ff ff ff    	je     18 <main+0x18>
  e2:	e8 c3 02 00 00       	call   3aa <fork>
  if (pid) pid = fork();
  e7:	85 c0                	test   %eax,%eax
  e9:	0f 84 29 ff ff ff    	je     18 <main+0x18>
  ef:	e8 b6 02 00 00       	call   3aa <fork>
  if (!pid) { // Se for o filho
  f4:	83 f8 00             	cmp    $0x0,%eax
  f7:	0f 84 1b ff ff ff    	je     18 <main+0x18>
  } else if (pid > 0) {
  fd:	7e 3c                	jle    13b <main+0x13b>
    printf(OUTPUT_STREAM, "Pai: %d\n", getpid());
  ff:	e8 2e 03 00 00       	call   432 <getpid>
 104:	52                   	push   %edx
 105:	50                   	push   %eax
 106:	68 63 08 00 00       	push   $0x863
 10b:	6a 01                	push   $0x1
 10d:	e8 ee 03 00 00       	call   500 <printf>
    printf(OUTPUT_STREAM, "Esperando filho terminar.\n");
 112:	59                   	pop    %ecx
 113:	5b                   	pop    %ebx
 114:	68 6c 08 00 00       	push   $0x86c
 119:	6a 01                	push   $0x1
 11b:	e8 e0 03 00 00       	call   500 <printf>
    wait();
 120:	e8 95 02 00 00       	call   3ba <wait>
    printf(OUTPUT_STREAM, "filho terminou.\n");
 125:	58                   	pop    %eax
 126:	5a                   	pop    %edx
 127:	68 87 08 00 00       	push   $0x887
 12c:	6a 01                	push   $0x1
 12e:	e8 cd 03 00 00       	call   500 <printf>
 133:	83 c4 10             	add    $0x10,%esp
 136:	e9 15 ff ff ff       	jmp    50 <main+0x50>
    printf(OUTPUT_STREAM, "Erro\n");
 13b:	50                   	push   %eax
 13c:	50                   	push   %eax
 13d:	68 98 08 00 00       	push   $0x898
 142:	6a 01                	push   $0x1
 144:	e8 b7 03 00 00       	call   500 <printf>
 149:	83 c4 10             	add    $0x10,%esp
 14c:	e9 ff fe ff ff       	jmp    50 <main+0x50>
 151:	66 90                	xchg   %ax,%ax
 153:	66 90                	xchg   %ax,%ax
 155:	66 90                	xchg   %ax,%ax
 157:	66 90                	xchg   %ax,%ax
 159:	66 90                	xchg   %ax,%ax
 15b:	66 90                	xchg   %ax,%ax
 15d:	66 90                	xchg   %ax,%ax
 15f:	90                   	nop

00000160 <strcpy>:
 160:	55                   	push   %ebp
 161:	89 e5                	mov    %esp,%ebp
 163:	53                   	push   %ebx
 164:	8b 45 08             	mov    0x8(%ebp),%eax
 167:	8b 4d 0c             	mov    0xc(%ebp),%ecx
 16a:	89 c2                	mov    %eax,%edx
 16c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 170:	83 c1 01             	add    $0x1,%ecx
 173:	0f b6 59 ff          	movzbl -0x1(%ecx),%ebx
 177:	83 c2 01             	add    $0x1,%edx
 17a:	84 db                	test   %bl,%bl
 17c:	88 5a ff             	mov    %bl,-0x1(%edx)
 17f:	75 ef                	jne    170 <strcpy+0x10>
 181:	5b                   	pop    %ebx
 182:	5d                   	pop    %ebp
 183:	c3                   	ret    
 184:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 18a:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00000190 <strcmp>:
 190:	55                   	push   %ebp
 191:	89 e5                	mov    %esp,%ebp
 193:	53                   	push   %ebx
 194:	8b 55 08             	mov    0x8(%ebp),%edx
 197:	8b 4d 0c             	mov    0xc(%ebp),%ecx
 19a:	0f b6 02             	movzbl (%edx),%eax
 19d:	0f b6 19             	movzbl (%ecx),%ebx
 1a0:	84 c0                	test   %al,%al
 1a2:	75 1c                	jne    1c0 <strcmp+0x30>
 1a4:	eb 2a                	jmp    1d0 <strcmp+0x40>
 1a6:	8d 76 00             	lea    0x0(%esi),%esi
 1a9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 1b0:	83 c2 01             	add    $0x1,%edx
 1b3:	0f b6 02             	movzbl (%edx),%eax
 1b6:	83 c1 01             	add    $0x1,%ecx
 1b9:	0f b6 19             	movzbl (%ecx),%ebx
 1bc:	84 c0                	test   %al,%al
 1be:	74 10                	je     1d0 <strcmp+0x40>
 1c0:	38 d8                	cmp    %bl,%al
 1c2:	74 ec                	je     1b0 <strcmp+0x20>
 1c4:	29 d8                	sub    %ebx,%eax
 1c6:	5b                   	pop    %ebx
 1c7:	5d                   	pop    %ebp
 1c8:	c3                   	ret    
 1c9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 1d0:	31 c0                	xor    %eax,%eax
 1d2:	29 d8                	sub    %ebx,%eax
 1d4:	5b                   	pop    %ebx
 1d5:	5d                   	pop    %ebp
 1d6:	c3                   	ret    
 1d7:	89 f6                	mov    %esi,%esi
 1d9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000001e0 <strlen>:
 1e0:	55                   	push   %ebp
 1e1:	89 e5                	mov    %esp,%ebp
 1e3:	8b 4d 08             	mov    0x8(%ebp),%ecx
 1e6:	80 39 00             	cmpb   $0x0,(%ecx)
 1e9:	74 15                	je     200 <strlen+0x20>
 1eb:	31 d2                	xor    %edx,%edx
 1ed:	8d 76 00             	lea    0x0(%esi),%esi
 1f0:	83 c2 01             	add    $0x1,%edx
 1f3:	80 3c 11 00          	cmpb   $0x0,(%ecx,%edx,1)
 1f7:	89 d0                	mov    %edx,%eax
 1f9:	75 f5                	jne    1f0 <strlen+0x10>
 1fb:	5d                   	pop    %ebp
 1fc:	c3                   	ret    
 1fd:	8d 76 00             	lea    0x0(%esi),%esi
 200:	31 c0                	xor    %eax,%eax
 202:	5d                   	pop    %ebp
 203:	c3                   	ret    
 204:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 20a:	8d bf 00 00 00 00    	lea    0x0(%edi),%edi

00000210 <memset>:
 210:	55                   	push   %ebp
 211:	89 e5                	mov    %esp,%ebp
 213:	57                   	push   %edi
 214:	8b 55 08             	mov    0x8(%ebp),%edx
 217:	8b 4d 10             	mov    0x10(%ebp),%ecx
 21a:	8b 45 0c             	mov    0xc(%ebp),%eax
 21d:	89 d7                	mov    %edx,%edi
 21f:	fc                   	cld    
 220:	f3 aa                	rep stos %al,%es:(%edi)
 222:	89 d0                	mov    %edx,%eax
 224:	5f                   	pop    %edi
 225:	5d                   	pop    %ebp
 226:	c3                   	ret    
 227:	89 f6                	mov    %esi,%esi
 229:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00000230 <strchr>:
 230:	55                   	push   %ebp
 231:	89 e5                	mov    %esp,%ebp
 233:	53                   	push   %ebx
 234:	8b 45 08             	mov    0x8(%ebp),%eax
 237:	8b 5d 0c             	mov    0xc(%ebp),%ebx
 23a:	0f b6 10             	movzbl (%eax),%edx
 23d:	84 d2                	test   %dl,%dl
 23f:	74 1d                	je     25e <strchr+0x2e>
 241:	38 d3                	cmp    %dl,%bl
 243:	89 d9                	mov    %ebx,%ecx
 245:	75 0d                	jne    254 <strchr+0x24>
 247:	eb 17                	jmp    260 <strchr+0x30>
 249:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 250:	38 ca                	cmp    %cl,%dl
 252:	74 0c                	je     260 <strchr+0x30>
 254:	83 c0 01             	add    $0x1,%eax
 257:	0f b6 10             	movzbl (%eax),%edx
 25a:	84 d2                	test   %dl,%dl
 25c:	75 f2                	jne    250 <strchr+0x20>
 25e:	31 c0                	xor    %eax,%eax
 260:	5b                   	pop    %ebx
 261:	5d                   	pop    %ebp
 262:	c3                   	ret    
 263:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 269:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00000270 <gets>:
 270:	55                   	push   %ebp
 271:	89 e5                	mov    %esp,%ebp
 273:	57                   	push   %edi
 274:	56                   	push   %esi
 275:	53                   	push   %ebx
 276:	31 f6                	xor    %esi,%esi
 278:	89 f3                	mov    %esi,%ebx
 27a:	83 ec 1c             	sub    $0x1c,%esp
 27d:	8b 7d 08             	mov    0x8(%ebp),%edi
 280:	eb 2f                	jmp    2b1 <gets+0x41>
 282:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 288:	8d 45 e7             	lea    -0x19(%ebp),%eax
 28b:	83 ec 04             	sub    $0x4,%esp
 28e:	6a 01                	push   $0x1
 290:	50                   	push   %eax
 291:	6a 00                	push   $0x0
 293:	e8 32 01 00 00       	call   3ca <read>
 298:	83 c4 10             	add    $0x10,%esp
 29b:	85 c0                	test   %eax,%eax
 29d:	7e 1c                	jle    2bb <gets+0x4b>
 29f:	0f b6 45 e7          	movzbl -0x19(%ebp),%eax
 2a3:	83 c7 01             	add    $0x1,%edi
 2a6:	88 47 ff             	mov    %al,-0x1(%edi)
 2a9:	3c 0a                	cmp    $0xa,%al
 2ab:	74 23                	je     2d0 <gets+0x60>
 2ad:	3c 0d                	cmp    $0xd,%al
 2af:	74 1f                	je     2d0 <gets+0x60>
 2b1:	83 c3 01             	add    $0x1,%ebx
 2b4:	3b 5d 0c             	cmp    0xc(%ebp),%ebx
 2b7:	89 fe                	mov    %edi,%esi
 2b9:	7c cd                	jl     288 <gets+0x18>
 2bb:	89 f3                	mov    %esi,%ebx
 2bd:	8b 45 08             	mov    0x8(%ebp),%eax
 2c0:	c6 03 00             	movb   $0x0,(%ebx)
 2c3:	8d 65 f4             	lea    -0xc(%ebp),%esp
 2c6:	5b                   	pop    %ebx
 2c7:	5e                   	pop    %esi
 2c8:	5f                   	pop    %edi
 2c9:	5d                   	pop    %ebp
 2ca:	c3                   	ret    
 2cb:	90                   	nop
 2cc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 2d0:	8b 75 08             	mov    0x8(%ebp),%esi
 2d3:	8b 45 08             	mov    0x8(%ebp),%eax
 2d6:	01 de                	add    %ebx,%esi
 2d8:	89 f3                	mov    %esi,%ebx
 2da:	c6 03 00             	movb   $0x0,(%ebx)
 2dd:	8d 65 f4             	lea    -0xc(%ebp),%esp
 2e0:	5b                   	pop    %ebx
 2e1:	5e                   	pop    %esi
 2e2:	5f                   	pop    %edi
 2e3:	5d                   	pop    %ebp
 2e4:	c3                   	ret    
 2e5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 2e9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

000002f0 <stat>:
 2f0:	55                   	push   %ebp
 2f1:	89 e5                	mov    %esp,%ebp
 2f3:	56                   	push   %esi
 2f4:	53                   	push   %ebx
 2f5:	83 ec 08             	sub    $0x8,%esp
 2f8:	6a 00                	push   $0x0
 2fa:	ff 75 08             	pushl  0x8(%ebp)
 2fd:	e8 f0 00 00 00       	call   3f2 <open>
 302:	83 c4 10             	add    $0x10,%esp
 305:	85 c0                	test   %eax,%eax
 307:	78 27                	js     330 <stat+0x40>
 309:	83 ec 08             	sub    $0x8,%esp
 30c:	ff 75 0c             	pushl  0xc(%ebp)
 30f:	89 c3                	mov    %eax,%ebx
 311:	50                   	push   %eax
 312:	e8 f3 00 00 00       	call   40a <fstat>
 317:	89 1c 24             	mov    %ebx,(%esp)
 31a:	89 c6                	mov    %eax,%esi
 31c:	e8 b9 00 00 00       	call   3da <close>
 321:	83 c4 10             	add    $0x10,%esp
 324:	8d 65 f8             	lea    -0x8(%ebp),%esp
 327:	89 f0                	mov    %esi,%eax
 329:	5b                   	pop    %ebx
 32a:	5e                   	pop    %esi
 32b:	5d                   	pop    %ebp
 32c:	c3                   	ret    
 32d:	8d 76 00             	lea    0x0(%esi),%esi
 330:	be ff ff ff ff       	mov    $0xffffffff,%esi
 335:	eb ed                	jmp    324 <stat+0x34>
 337:	89 f6                	mov    %esi,%esi
 339:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

00000340 <atoi>:
 340:	55                   	push   %ebp
 341:	89 e5                	mov    %esp,%ebp
 343:	53                   	push   %ebx
 344:	8b 4d 08             	mov    0x8(%ebp),%ecx
 347:	0f be 11             	movsbl (%ecx),%edx
 34a:	8d 42 d0             	lea    -0x30(%edx),%eax
 34d:	3c 09                	cmp    $0x9,%al
 34f:	b8 00 00 00 00       	mov    $0x0,%eax
 354:	77 1f                	ja     375 <atoi+0x35>
 356:	8d 76 00             	lea    0x0(%esi),%esi
 359:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 360:	8d 04 80             	lea    (%eax,%eax,4),%eax
 363:	83 c1 01             	add    $0x1,%ecx
 366:	8d 44 42 d0          	lea    -0x30(%edx,%eax,2),%eax
 36a:	0f be 11             	movsbl (%ecx),%edx
 36d:	8d 5a d0             	lea    -0x30(%edx),%ebx
 370:	80 fb 09             	cmp    $0x9,%bl
 373:	76 eb                	jbe    360 <atoi+0x20>
 375:	5b                   	pop    %ebx
 376:	5d                   	pop    %ebp
 377:	c3                   	ret    
 378:	90                   	nop
 379:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000380 <memmove>:
 380:	55                   	push   %ebp
 381:	89 e5                	mov    %esp,%ebp
 383:	56                   	push   %esi
 384:	53                   	push   %ebx
 385:	8b 5d 10             	mov    0x10(%ebp),%ebx
 388:	8b 45 08             	mov    0x8(%ebp),%eax
 38b:	8b 75 0c             	mov    0xc(%ebp),%esi
 38e:	85 db                	test   %ebx,%ebx
 390:	7e 14                	jle    3a6 <memmove+0x26>
 392:	31 d2                	xor    %edx,%edx
 394:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 398:	0f b6 0c 16          	movzbl (%esi,%edx,1),%ecx
 39c:	88 0c 10             	mov    %cl,(%eax,%edx,1)
 39f:	83 c2 01             	add    $0x1,%edx
 3a2:	39 d3                	cmp    %edx,%ebx
 3a4:	75 f2                	jne    398 <memmove+0x18>
 3a6:	5b                   	pop    %ebx
 3a7:	5e                   	pop    %esi
 3a8:	5d                   	pop    %ebp
 3a9:	c3                   	ret    

000003aa <fork>:
 3aa:	b8 01 00 00 00       	mov    $0x1,%eax
 3af:	cd 40                	int    $0x40
 3b1:	c3                   	ret    

000003b2 <exit>:
 3b2:	b8 02 00 00 00       	mov    $0x2,%eax
 3b7:	cd 40                	int    $0x40
 3b9:	c3                   	ret    

000003ba <wait>:
 3ba:	b8 03 00 00 00       	mov    $0x3,%eax
 3bf:	cd 40                	int    $0x40
 3c1:	c3                   	ret    

000003c2 <pipe>:
 3c2:	b8 04 00 00 00       	mov    $0x4,%eax
 3c7:	cd 40                	int    $0x40
 3c9:	c3                   	ret    

000003ca <read>:
 3ca:	b8 05 00 00 00       	mov    $0x5,%eax
 3cf:	cd 40                	int    $0x40
 3d1:	c3                   	ret    

000003d2 <write>:
 3d2:	b8 10 00 00 00       	mov    $0x10,%eax
 3d7:	cd 40                	int    $0x40
 3d9:	c3                   	ret    

000003da <close>:
 3da:	b8 15 00 00 00       	mov    $0x15,%eax
 3df:	cd 40                	int    $0x40
 3e1:	c3                   	ret    

000003e2 <kill>:
 3e2:	b8 06 00 00 00       	mov    $0x6,%eax
 3e7:	cd 40                	int    $0x40
 3e9:	c3                   	ret    

000003ea <exec>:
 3ea:	b8 07 00 00 00       	mov    $0x7,%eax
 3ef:	cd 40                	int    $0x40
 3f1:	c3                   	ret    

000003f2 <open>:
 3f2:	b8 0f 00 00 00       	mov    $0xf,%eax
 3f7:	cd 40                	int    $0x40
 3f9:	c3                   	ret    

000003fa <mknod>:
 3fa:	b8 11 00 00 00       	mov    $0x11,%eax
 3ff:	cd 40                	int    $0x40
 401:	c3                   	ret    

00000402 <unlink>:
 402:	b8 12 00 00 00       	mov    $0x12,%eax
 407:	cd 40                	int    $0x40
 409:	c3                   	ret    

0000040a <fstat>:
 40a:	b8 08 00 00 00       	mov    $0x8,%eax
 40f:	cd 40                	int    $0x40
 411:	c3                   	ret    

00000412 <link>:
 412:	b8 13 00 00 00       	mov    $0x13,%eax
 417:	cd 40                	int    $0x40
 419:	c3                   	ret    

0000041a <mkdir>:
 41a:	b8 14 00 00 00       	mov    $0x14,%eax
 41f:	cd 40                	int    $0x40
 421:	c3                   	ret    

00000422 <chdir>:
 422:	b8 09 00 00 00       	mov    $0x9,%eax
 427:	cd 40                	int    $0x40
 429:	c3                   	ret    

0000042a <dup>:
 42a:	b8 0a 00 00 00       	mov    $0xa,%eax
 42f:	cd 40                	int    $0x40
 431:	c3                   	ret    

00000432 <getpid>:
 432:	b8 0b 00 00 00       	mov    $0xb,%eax
 437:	cd 40                	int    $0x40
 439:	c3                   	ret    

0000043a <sbrk>:
 43a:	b8 0c 00 00 00       	mov    $0xc,%eax
 43f:	cd 40                	int    $0x40
 441:	c3                   	ret    

00000442 <sleep>:
 442:	b8 0d 00 00 00       	mov    $0xd,%eax
 447:	cd 40                	int    $0x40
 449:	c3                   	ret    

0000044a <uptime>:
 44a:	b8 0e 00 00 00       	mov    $0xe,%eax
 44f:	cd 40                	int    $0x40
 451:	c3                   	ret    
 452:	66 90                	xchg   %ax,%ax
 454:	66 90                	xchg   %ax,%ax
 456:	66 90                	xchg   %ax,%ax
 458:	66 90                	xchg   %ax,%ax
 45a:	66 90                	xchg   %ax,%ax
 45c:	66 90                	xchg   %ax,%ax
 45e:	66 90                	xchg   %ax,%ax

00000460 <printint>:
 460:	55                   	push   %ebp
 461:	89 e5                	mov    %esp,%ebp
 463:	57                   	push   %edi
 464:	56                   	push   %esi
 465:	53                   	push   %ebx
 466:	83 ec 3c             	sub    $0x3c,%esp
 469:	85 d2                	test   %edx,%edx
 46b:	89 45 c0             	mov    %eax,-0x40(%ebp)
 46e:	89 d0                	mov    %edx,%eax
 470:	79 76                	jns    4e8 <printint+0x88>
 472:	f6 45 08 01          	testb  $0x1,0x8(%ebp)
 476:	74 70                	je     4e8 <printint+0x88>
 478:	f7 d8                	neg    %eax
 47a:	c7 45 c4 01 00 00 00 	movl   $0x1,-0x3c(%ebp)
 481:	31 f6                	xor    %esi,%esi
 483:	8d 5d d7             	lea    -0x29(%ebp),%ebx
 486:	eb 0a                	jmp    492 <printint+0x32>
 488:	90                   	nop
 489:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 490:	89 fe                	mov    %edi,%esi
 492:	31 d2                	xor    %edx,%edx
 494:	8d 7e 01             	lea    0x1(%esi),%edi
 497:	f7 f1                	div    %ecx
 499:	0f b6 92 a8 08 00 00 	movzbl 0x8a8(%edx),%edx
 4a0:	85 c0                	test   %eax,%eax
 4a2:	88 14 3b             	mov    %dl,(%ebx,%edi,1)
 4a5:	75 e9                	jne    490 <printint+0x30>
 4a7:	8b 45 c4             	mov    -0x3c(%ebp),%eax
 4aa:	85 c0                	test   %eax,%eax
 4ac:	74 08                	je     4b6 <printint+0x56>
 4ae:	c6 44 3d d8 2d       	movb   $0x2d,-0x28(%ebp,%edi,1)
 4b3:	8d 7e 02             	lea    0x2(%esi),%edi
 4b6:	8d 74 3d d7          	lea    -0x29(%ebp,%edi,1),%esi
 4ba:	8b 7d c0             	mov    -0x40(%ebp),%edi
 4bd:	8d 76 00             	lea    0x0(%esi),%esi
 4c0:	0f b6 06             	movzbl (%esi),%eax
 4c3:	83 ec 04             	sub    $0x4,%esp
 4c6:	83 ee 01             	sub    $0x1,%esi
 4c9:	6a 01                	push   $0x1
 4cb:	53                   	push   %ebx
 4cc:	57                   	push   %edi
 4cd:	88 45 d7             	mov    %al,-0x29(%ebp)
 4d0:	e8 fd fe ff ff       	call   3d2 <write>
 4d5:	83 c4 10             	add    $0x10,%esp
 4d8:	39 de                	cmp    %ebx,%esi
 4da:	75 e4                	jne    4c0 <printint+0x60>
 4dc:	8d 65 f4             	lea    -0xc(%ebp),%esp
 4df:	5b                   	pop    %ebx
 4e0:	5e                   	pop    %esi
 4e1:	5f                   	pop    %edi
 4e2:	5d                   	pop    %ebp
 4e3:	c3                   	ret    
 4e4:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 4e8:	c7 45 c4 00 00 00 00 	movl   $0x0,-0x3c(%ebp)
 4ef:	eb 90                	jmp    481 <printint+0x21>
 4f1:	eb 0d                	jmp    500 <printf>
 4f3:	90                   	nop
 4f4:	90                   	nop
 4f5:	90                   	nop
 4f6:	90                   	nop
 4f7:	90                   	nop
 4f8:	90                   	nop
 4f9:	90                   	nop
 4fa:	90                   	nop
 4fb:	90                   	nop
 4fc:	90                   	nop
 4fd:	90                   	nop
 4fe:	90                   	nop
 4ff:	90                   	nop

00000500 <printf>:
 500:	55                   	push   %ebp
 501:	89 e5                	mov    %esp,%ebp
 503:	57                   	push   %edi
 504:	56                   	push   %esi
 505:	53                   	push   %ebx
 506:	83 ec 2c             	sub    $0x2c,%esp
 509:	8b 75 0c             	mov    0xc(%ebp),%esi
 50c:	0f b6 1e             	movzbl (%esi),%ebx
 50f:	84 db                	test   %bl,%bl
 511:	0f 84 b3 00 00 00    	je     5ca <printf+0xca>
 517:	8d 45 10             	lea    0x10(%ebp),%eax
 51a:	83 c6 01             	add    $0x1,%esi
 51d:	31 ff                	xor    %edi,%edi
 51f:	89 45 d4             	mov    %eax,-0x2c(%ebp)
 522:	eb 2f                	jmp    553 <printf+0x53>
 524:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 528:	83 f8 25             	cmp    $0x25,%eax
 52b:	0f 84 a7 00 00 00    	je     5d8 <printf+0xd8>
 531:	8d 45 e2             	lea    -0x1e(%ebp),%eax
 534:	83 ec 04             	sub    $0x4,%esp
 537:	88 5d e2             	mov    %bl,-0x1e(%ebp)
 53a:	6a 01                	push   $0x1
 53c:	50                   	push   %eax
 53d:	ff 75 08             	pushl  0x8(%ebp)
 540:	e8 8d fe ff ff       	call   3d2 <write>
 545:	83 c4 10             	add    $0x10,%esp
 548:	83 c6 01             	add    $0x1,%esi
 54b:	0f b6 5e ff          	movzbl -0x1(%esi),%ebx
 54f:	84 db                	test   %bl,%bl
 551:	74 77                	je     5ca <printf+0xca>
 553:	85 ff                	test   %edi,%edi
 555:	0f be cb             	movsbl %bl,%ecx
 558:	0f b6 c3             	movzbl %bl,%eax
 55b:	74 cb                	je     528 <printf+0x28>
 55d:	83 ff 25             	cmp    $0x25,%edi
 560:	75 e6                	jne    548 <printf+0x48>
 562:	83 f8 64             	cmp    $0x64,%eax
 565:	0f 84 05 01 00 00    	je     670 <printf+0x170>
 56b:	81 e1 f7 00 00 00    	and    $0xf7,%ecx
 571:	83 f9 70             	cmp    $0x70,%ecx
 574:	74 72                	je     5e8 <printf+0xe8>
 576:	83 f8 73             	cmp    $0x73,%eax
 579:	0f 84 99 00 00 00    	je     618 <printf+0x118>
 57f:	83 f8 63             	cmp    $0x63,%eax
 582:	0f 84 08 01 00 00    	je     690 <printf+0x190>
 588:	83 f8 25             	cmp    $0x25,%eax
 58b:	0f 84 ef 00 00 00    	je     680 <printf+0x180>
 591:	8d 45 e7             	lea    -0x19(%ebp),%eax
 594:	83 ec 04             	sub    $0x4,%esp
 597:	c6 45 e7 25          	movb   $0x25,-0x19(%ebp)
 59b:	6a 01                	push   $0x1
 59d:	50                   	push   %eax
 59e:	ff 75 08             	pushl  0x8(%ebp)
 5a1:	e8 2c fe ff ff       	call   3d2 <write>
 5a6:	83 c4 0c             	add    $0xc,%esp
 5a9:	8d 45 e6             	lea    -0x1a(%ebp),%eax
 5ac:	88 5d e6             	mov    %bl,-0x1a(%ebp)
 5af:	6a 01                	push   $0x1
 5b1:	50                   	push   %eax
 5b2:	ff 75 08             	pushl  0x8(%ebp)
 5b5:	83 c6 01             	add    $0x1,%esi
 5b8:	31 ff                	xor    %edi,%edi
 5ba:	e8 13 fe ff ff       	call   3d2 <write>
 5bf:	0f b6 5e ff          	movzbl -0x1(%esi),%ebx
 5c3:	83 c4 10             	add    $0x10,%esp
 5c6:	84 db                	test   %bl,%bl
 5c8:	75 89                	jne    553 <printf+0x53>
 5ca:	8d 65 f4             	lea    -0xc(%ebp),%esp
 5cd:	5b                   	pop    %ebx
 5ce:	5e                   	pop    %esi
 5cf:	5f                   	pop    %edi
 5d0:	5d                   	pop    %ebp
 5d1:	c3                   	ret    
 5d2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 5d8:	bf 25 00 00 00       	mov    $0x25,%edi
 5dd:	e9 66 ff ff ff       	jmp    548 <printf+0x48>
 5e2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 5e8:	83 ec 0c             	sub    $0xc,%esp
 5eb:	b9 10 00 00 00       	mov    $0x10,%ecx
 5f0:	6a 00                	push   $0x0
 5f2:	8b 7d d4             	mov    -0x2c(%ebp),%edi
 5f5:	8b 45 08             	mov    0x8(%ebp),%eax
 5f8:	8b 17                	mov    (%edi),%edx
 5fa:	e8 61 fe ff ff       	call   460 <printint>
 5ff:	89 f8                	mov    %edi,%eax
 601:	83 c4 10             	add    $0x10,%esp
 604:	31 ff                	xor    %edi,%edi
 606:	83 c0 04             	add    $0x4,%eax
 609:	89 45 d4             	mov    %eax,-0x2c(%ebp)
 60c:	e9 37 ff ff ff       	jmp    548 <printf+0x48>
 611:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 618:	8b 45 d4             	mov    -0x2c(%ebp),%eax
 61b:	8b 08                	mov    (%eax),%ecx
 61d:	83 c0 04             	add    $0x4,%eax
 620:	89 45 d4             	mov    %eax,-0x2c(%ebp)
 623:	85 c9                	test   %ecx,%ecx
 625:	0f 84 8e 00 00 00    	je     6b9 <printf+0x1b9>
 62b:	0f b6 01             	movzbl (%ecx),%eax
 62e:	31 ff                	xor    %edi,%edi
 630:	89 cb                	mov    %ecx,%ebx
 632:	84 c0                	test   %al,%al
 634:	0f 84 0e ff ff ff    	je     548 <printf+0x48>
 63a:	89 75 d0             	mov    %esi,-0x30(%ebp)
 63d:	89 de                	mov    %ebx,%esi
 63f:	8b 5d 08             	mov    0x8(%ebp),%ebx
 642:	8d 7d e3             	lea    -0x1d(%ebp),%edi
 645:	8d 76 00             	lea    0x0(%esi),%esi
 648:	83 ec 04             	sub    $0x4,%esp
 64b:	83 c6 01             	add    $0x1,%esi
 64e:	88 45 e3             	mov    %al,-0x1d(%ebp)
 651:	6a 01                	push   $0x1
 653:	57                   	push   %edi
 654:	53                   	push   %ebx
 655:	e8 78 fd ff ff       	call   3d2 <write>
 65a:	0f b6 06             	movzbl (%esi),%eax
 65d:	83 c4 10             	add    $0x10,%esp
 660:	84 c0                	test   %al,%al
 662:	75 e4                	jne    648 <printf+0x148>
 664:	8b 75 d0             	mov    -0x30(%ebp),%esi
 667:	31 ff                	xor    %edi,%edi
 669:	e9 da fe ff ff       	jmp    548 <printf+0x48>
 66e:	66 90                	xchg   %ax,%ax
 670:	83 ec 0c             	sub    $0xc,%esp
 673:	b9 0a 00 00 00       	mov    $0xa,%ecx
 678:	6a 01                	push   $0x1
 67a:	e9 73 ff ff ff       	jmp    5f2 <printf+0xf2>
 67f:	90                   	nop
 680:	83 ec 04             	sub    $0x4,%esp
 683:	88 5d e5             	mov    %bl,-0x1b(%ebp)
 686:	8d 45 e5             	lea    -0x1b(%ebp),%eax
 689:	6a 01                	push   $0x1
 68b:	e9 21 ff ff ff       	jmp    5b1 <printf+0xb1>
 690:	8b 7d d4             	mov    -0x2c(%ebp),%edi
 693:	83 ec 04             	sub    $0x4,%esp
 696:	8b 07                	mov    (%edi),%eax
 698:	6a 01                	push   $0x1
 69a:	83 c7 04             	add    $0x4,%edi
 69d:	88 45 e4             	mov    %al,-0x1c(%ebp)
 6a0:	8d 45 e4             	lea    -0x1c(%ebp),%eax
 6a3:	50                   	push   %eax
 6a4:	ff 75 08             	pushl  0x8(%ebp)
 6a7:	e8 26 fd ff ff       	call   3d2 <write>
 6ac:	89 7d d4             	mov    %edi,-0x2c(%ebp)
 6af:	83 c4 10             	add    $0x10,%esp
 6b2:	31 ff                	xor    %edi,%edi
 6b4:	e9 8f fe ff ff       	jmp    548 <printf+0x48>
 6b9:	bb 9e 08 00 00       	mov    $0x89e,%ebx
 6be:	b8 28 00 00 00       	mov    $0x28,%eax
 6c3:	e9 72 ff ff ff       	jmp    63a <printf+0x13a>
 6c8:	66 90                	xchg   %ax,%ax
 6ca:	66 90                	xchg   %ax,%ax
 6cc:	66 90                	xchg   %ax,%ax
 6ce:	66 90                	xchg   %ax,%ax

000006d0 <free>:
 6d0:	55                   	push   %ebp
 6d1:	a1 50 0b 00 00       	mov    0xb50,%eax
 6d6:	89 e5                	mov    %esp,%ebp
 6d8:	57                   	push   %edi
 6d9:	56                   	push   %esi
 6da:	53                   	push   %ebx
 6db:	8b 5d 08             	mov    0x8(%ebp),%ebx
 6de:	8d 4b f8             	lea    -0x8(%ebx),%ecx
 6e1:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 6e8:	39 c8                	cmp    %ecx,%eax
 6ea:	8b 10                	mov    (%eax),%edx
 6ec:	73 32                	jae    720 <free+0x50>
 6ee:	39 d1                	cmp    %edx,%ecx
 6f0:	72 04                	jb     6f6 <free+0x26>
 6f2:	39 d0                	cmp    %edx,%eax
 6f4:	72 32                	jb     728 <free+0x58>
 6f6:	8b 73 fc             	mov    -0x4(%ebx),%esi
 6f9:	8d 3c f1             	lea    (%ecx,%esi,8),%edi
 6fc:	39 fa                	cmp    %edi,%edx
 6fe:	74 30                	je     730 <free+0x60>
 700:	89 53 f8             	mov    %edx,-0x8(%ebx)
 703:	8b 50 04             	mov    0x4(%eax),%edx
 706:	8d 34 d0             	lea    (%eax,%edx,8),%esi
 709:	39 f1                	cmp    %esi,%ecx
 70b:	74 3a                	je     747 <free+0x77>
 70d:	89 08                	mov    %ecx,(%eax)
 70f:	a3 50 0b 00 00       	mov    %eax,0xb50
 714:	5b                   	pop    %ebx
 715:	5e                   	pop    %esi
 716:	5f                   	pop    %edi
 717:	5d                   	pop    %ebp
 718:	c3                   	ret    
 719:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 720:	39 d0                	cmp    %edx,%eax
 722:	72 04                	jb     728 <free+0x58>
 724:	39 d1                	cmp    %edx,%ecx
 726:	72 ce                	jb     6f6 <free+0x26>
 728:	89 d0                	mov    %edx,%eax
 72a:	eb bc                	jmp    6e8 <free+0x18>
 72c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 730:	03 72 04             	add    0x4(%edx),%esi
 733:	89 73 fc             	mov    %esi,-0x4(%ebx)
 736:	8b 10                	mov    (%eax),%edx
 738:	8b 12                	mov    (%edx),%edx
 73a:	89 53 f8             	mov    %edx,-0x8(%ebx)
 73d:	8b 50 04             	mov    0x4(%eax),%edx
 740:	8d 34 d0             	lea    (%eax,%edx,8),%esi
 743:	39 f1                	cmp    %esi,%ecx
 745:	75 c6                	jne    70d <free+0x3d>
 747:	03 53 fc             	add    -0x4(%ebx),%edx
 74a:	a3 50 0b 00 00       	mov    %eax,0xb50
 74f:	89 50 04             	mov    %edx,0x4(%eax)
 752:	8b 53 f8             	mov    -0x8(%ebx),%edx
 755:	89 10                	mov    %edx,(%eax)
 757:	5b                   	pop    %ebx
 758:	5e                   	pop    %esi
 759:	5f                   	pop    %edi
 75a:	5d                   	pop    %ebp
 75b:	c3                   	ret    
 75c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00000760 <malloc>:
 760:	55                   	push   %ebp
 761:	89 e5                	mov    %esp,%ebp
 763:	57                   	push   %edi
 764:	56                   	push   %esi
 765:	53                   	push   %ebx
 766:	83 ec 0c             	sub    $0xc,%esp
 769:	8b 45 08             	mov    0x8(%ebp),%eax
 76c:	8b 15 50 0b 00 00    	mov    0xb50,%edx
 772:	8d 78 07             	lea    0x7(%eax),%edi
 775:	c1 ef 03             	shr    $0x3,%edi
 778:	83 c7 01             	add    $0x1,%edi
 77b:	85 d2                	test   %edx,%edx
 77d:	0f 84 9d 00 00 00    	je     820 <malloc+0xc0>
 783:	8b 02                	mov    (%edx),%eax
 785:	8b 48 04             	mov    0x4(%eax),%ecx
 788:	39 cf                	cmp    %ecx,%edi
 78a:	76 6c                	jbe    7f8 <malloc+0x98>
 78c:	81 ff 00 10 00 00    	cmp    $0x1000,%edi
 792:	bb 00 10 00 00       	mov    $0x1000,%ebx
 797:	0f 43 df             	cmovae %edi,%ebx
 79a:	8d 34 dd 00 00 00 00 	lea    0x0(,%ebx,8),%esi
 7a1:	eb 0e                	jmp    7b1 <malloc+0x51>
 7a3:	90                   	nop
 7a4:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 7a8:	8b 02                	mov    (%edx),%eax
 7aa:	8b 48 04             	mov    0x4(%eax),%ecx
 7ad:	39 f9                	cmp    %edi,%ecx
 7af:	73 47                	jae    7f8 <malloc+0x98>
 7b1:	39 05 50 0b 00 00    	cmp    %eax,0xb50
 7b7:	89 c2                	mov    %eax,%edx
 7b9:	75 ed                	jne    7a8 <malloc+0x48>
 7bb:	83 ec 0c             	sub    $0xc,%esp
 7be:	56                   	push   %esi
 7bf:	e8 76 fc ff ff       	call   43a <sbrk>
 7c4:	83 c4 10             	add    $0x10,%esp
 7c7:	83 f8 ff             	cmp    $0xffffffff,%eax
 7ca:	74 1c                	je     7e8 <malloc+0x88>
 7cc:	89 58 04             	mov    %ebx,0x4(%eax)
 7cf:	83 ec 0c             	sub    $0xc,%esp
 7d2:	83 c0 08             	add    $0x8,%eax
 7d5:	50                   	push   %eax
 7d6:	e8 f5 fe ff ff       	call   6d0 <free>
 7db:	8b 15 50 0b 00 00    	mov    0xb50,%edx
 7e1:	83 c4 10             	add    $0x10,%esp
 7e4:	85 d2                	test   %edx,%edx
 7e6:	75 c0                	jne    7a8 <malloc+0x48>
 7e8:	8d 65 f4             	lea    -0xc(%ebp),%esp
 7eb:	31 c0                	xor    %eax,%eax
 7ed:	5b                   	pop    %ebx
 7ee:	5e                   	pop    %esi
 7ef:	5f                   	pop    %edi
 7f0:	5d                   	pop    %ebp
 7f1:	c3                   	ret    
 7f2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 7f8:	39 cf                	cmp    %ecx,%edi
 7fa:	74 54                	je     850 <malloc+0xf0>
 7fc:	29 f9                	sub    %edi,%ecx
 7fe:	89 48 04             	mov    %ecx,0x4(%eax)
 801:	8d 04 c8             	lea    (%eax,%ecx,8),%eax
 804:	89 78 04             	mov    %edi,0x4(%eax)
 807:	89 15 50 0b 00 00    	mov    %edx,0xb50
 80d:	8d 65 f4             	lea    -0xc(%ebp),%esp
 810:	83 c0 08             	add    $0x8,%eax
 813:	5b                   	pop    %ebx
 814:	5e                   	pop    %esi
 815:	5f                   	pop    %edi
 816:	5d                   	pop    %ebp
 817:	c3                   	ret    
 818:	90                   	nop
 819:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 820:	c7 05 50 0b 00 00 54 	movl   $0xb54,0xb50
 827:	0b 00 00 
 82a:	c7 05 54 0b 00 00 54 	movl   $0xb54,0xb54
 831:	0b 00 00 
 834:	b8 54 0b 00 00       	mov    $0xb54,%eax
 839:	c7 05 58 0b 00 00 00 	movl   $0x0,0xb58
 840:	00 00 00 
 843:	e9 44 ff ff ff       	jmp    78c <malloc+0x2c>
 848:	90                   	nop
 849:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
 850:	8b 08                	mov    (%eax),%ecx
 852:	89 0a                	mov    %ecx,(%edx)
 854:	eb b1                	jmp    807 <malloc+0xa7>
