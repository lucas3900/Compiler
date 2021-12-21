.source     passingInterfaces.decaf
.class      public passingInterfaces
.super      java/lang/Object 

.method                 public <init>()V
   .limit stack         1
   .limit locals        1
   aload_0
   invokespecial        java/lang/Object/<init>()V
   return
.end method

.method			public static main()V
   .limit stack		100
   .limit locals            3
   new                  C
   dup
   invokespecial        C/<init>()V
   astore               0
   aload                0
   iconst_4
   invokevirtual        C/setter(I)V 
   new                  C
   dup
   invokespecial        C/<init>()V
   astore               1
   aload                1
   ldc                  7
   invokevirtual        C/setter(I)V 
   aload                1
   astore               2
   aload                0
   aload                2
   invokevirtual        C/cmp(LA;)V 
   return
   nop
.end method

.method                 public static main([Ljava/lang/String;)V
   .limit stack         0
   .limit locals        1
   invokestatic         passingInterfaces/main()V
   return
.end method
