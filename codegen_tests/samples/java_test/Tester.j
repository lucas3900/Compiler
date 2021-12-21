.source                  Tester.java
.class                   public Tester
.super                   java/lang/Object


.method                  public <init>()V
   .limit stack          1
   .limit locals         1
   .line                 1
   aload_0               
   invokespecial         java/lang/Object/<init>()V
   return                
.end method              

.method                  public static get_int([I)I
   .limit stack          2
   .limit locals         1
   .line                 4
   aload_0               
   iconst_3              
   iaload                
   ireturn               
.end method              

.method                  public static main()V
   .limit stack          3
   .limit locals         1
   .line                 9
   bipush                48
   newarray              int
   astore_0              
   .line                 10
   aload_0               
   iconst_3              
   bipush                56
   iastore               
   .line                 11
   aload_0               
   invokestatic          Tester/get_int([I)I
   pop                   
   .line                 12
   return                
.end method              

.method                  public static main([Ljava/lang/String;)V
   .limit stack          0
   .limit locals         1
   .line                 15
   invokestatic          Tester/main()V
   .line                 16
   return                
.end method              

