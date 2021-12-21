.source     passingInterfaces.decaf
.class      public B
.super      java/lang/Object
.field          q I

.method                 public <init>()V
   .limit stack         1
   .limit locals        1
   aload_0
   invokespecial        java/lang/Object/<init>()V
   return
.end method

.method			public setter(I)V
   .limit stack		100
   .limit locals            2
   aload_0
   iload                1
   putfield             B/q I
   return
   nop
.end method

.method                 public static main([Ljava/lang/String;)V
   .limit stack         0
   .limit locals        1
   invokestatic         B/main()V
   return
.end method
