.source     passingInterfaces.decaf
.class      public C
.super      B

.implements         A

.method                 public <init>()V
   .limit stack         1
   .limit locals        1
   aload_0
   invokespecial        B/<init>()V
   return
.end method

.method			public foo(I)V
   .limit stack		100
   .limit locals            2
   getstatic            java/lang/System/out Ljava/io/PrintStream;
   iload                1
   invokevirtual        java/io/PrintStream/print(I)V
   getstatic            java/lang/System/out Ljava/io/PrintStream;
   ldc                  ""
   invokevirtual        java/io/PrintStream/println(Ljava/lang/String;)V
   return
   nop
.end method

.method			public getter()I
   .limit stack		100
   .limit locals            1
   aload_0
   getfield             B/q I
   ireturn
   nop
.end method

.method			public cmp(LA;)V
   .limit stack		100
   .limit locals            2
   getstatic            java/lang/System/out Ljava/io/PrintStream;
   aload_0
   getfield             C/q I
   aload                1
   invokeinterface      A/getter()I 1
   if_icmpgt            L1
   iconst_0
   goto                 L2
L1:
   iconst_1
L2:
   invokevirtual        java/io/PrintStream/print(Z)V
   getstatic            java/lang/System/out Ljava/io/PrintStream;
   ldc                  ""
   invokevirtual        java/io/PrintStream/println(Ljava/lang/String;)V
   return
   nop
.end method

.method                 public static main([Ljava/lang/String;)V
   .limit stack         0
   .limit locals        1
   invokestatic         C/main()V
   return
.end method
