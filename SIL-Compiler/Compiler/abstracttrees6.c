struct Tnode *TreeCreate(int TYPE,int NODETYPE,int VALUE,char *NAME,struct Tnode *ArgList,struct Tnode *Ptr1,struct Tnode *Ptr2,struct Tnode *Ptr3){
    struct Tnode *temp;
    switch(NODETYPE){
    	case NODETYPE_IF    : if(Ptr1->TYPE != TYPE_BOOLEAN){
    			 	yyerror("unexpected type of expression in if");exit(0);}
    			      break;
    	case NODETYPE_WHILE : if(Ptr1->TYPE != TYPE_BOOLEAN){
    			 	yyerror("unexpected type of expression in while");exit(0);}
    			      break;
    	case NODETYPE_PLUS  : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
    			 	yyerror("mismatching operands for plus operation");exit(0);}
    	  		      break;
    	case NODETYPE_MINUS  : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
                    yyerror("mismatching operands for minus operation");exit(0);}
                      break;
        case NODETYPE_MOD  : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
                    yyerror("mismatching operands for mod operation");exit(0);}
                      break;
        case NODETYPE_DIV  : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
                    yyerror("mismatching operands for div operation");exit(0);}
                      break;
        case NODETYPE_MUL   : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
       		 		yyerror("mismatching operands for multiplication operation");exit(0);}
  		  	          break;
    	case NODETYPE_GT    : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
    			 	yyerror("mismatching operands for greater than relational operation");exit(0);}
    			      break;
    	case NODETYPE_LT    : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
    			 	yyerror("mismatching operands for lesser than relational operation");exit(0);}
    			      break;
    	case NODETYPE_EQ    : if(!((Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT) || (Ptr1->TYPE == TYPE_BOOLEAN && Ptr2->TYPE == TYPE_BOOLEAN))){
    			 	//printf("%d %d\n",Ptr1->TYPE,Ptr2->TYPE);
            yyerror("mismatching operands for equal to relational operation");exit(0);}
    			      break;
        case NODETYPE_GE    : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
                    yyerror("mismatching operands for greater than relational operation");exit(0);}
                      break;
        case NODETYPE_LE    : if(!(Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT)){
                    yyerror("mismatching operands for lesser than relational operation");exit(0);}
                      break;
        case NODETYPE_NE    : if(!((Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT) || (Ptr1->TYPE == TYPE_BOOLEAN && Ptr2->TYPE == TYPE_BOOLEAN))){
                    yyerror("mismatching operands for equal to relational operation");exit(0);}
                      break;
		case NODETYPE_AND   : if(!(Ptr1->TYPE == TYPE_BOOLEAN && Ptr2->TYPE == TYPE_BOOLEAN)){
                    yyerror("mismatching operands for AND logical operation");exit(0);}
                      break;
		case NODETYPE_OR   : if(!(Ptr1->TYPE == TYPE_BOOLEAN && Ptr2->TYPE == TYPE_BOOLEAN)){
                    yyerror("mismatching operands for OR logical operation");exit(0);}
                      break;
    	case NODETYPE_ASGN  : if(!((Ptr1->TYPE == TYPE_INT && Ptr2->TYPE == TYPE_INT) || (Ptr1->TYPE == TYPE_BOOLEAN && Ptr2->TYPE == TYPE_BOOLEAN))){
    				//printf("%d %d\n",Ptr1->TYPE,Ptr2->TYPE);
            yyerror("1.unexpected type of value for the variable");exit(0);}
                      break; 
    	case NODETYPE_ARR_ASGN : if(!((Ptr1->TYPE == TYPE_INT && Ptr3->TYPE == TYPE_INT) || (Ptr1->TYPE == TYPE_BOOLEAN && Ptr3->TYPE == TYPE_BOOLEAN)) || Ptr2->TYPE != TYPE_INT){
    				yyerror("2.unexpected type of value for the variable");exit(0);}
                      break;
        case NODETYPE_ARR_READ :
                      if(Ptr2->TYPE != TYPE_INT){
                        yyerror("2.unexpected type of value for the index of an array");exit(0);
                      }
                      break;
        case NODETYPE_ARR_ID:
                      if(Ptr2->TYPE != TYPE_INT){
                        yyerror("2.unexpected type of value for the index of an array");exit(0);
                      }
                      break;
        case NODETYPE_FUNCTION : 
                Gtemp = Glookup(NAME);
                Argtemp = Gtemp->Arglist;
                temp = ArgList;
				if(temp != NULL){
                	while(Argtemp != NULL && temp != NULL){
                	   if(!((temp->Ptr2->TYPE == TYPE_INT && Argtemp->type == STYPE_INT) ||(temp->Ptr2->TYPE == TYPE_BOOLEAN && Argtemp->type == STYPE_BOOLEAN)||(temp->Ptr2->TYPE == TYPE_PAIR && Argtemp->type == STYPE_PAIR))){
                	        printf("unmatching types passed for the function %s",NAME);yyerror("\n");exit(0);
                	   }
                     if((temp->Ptr2->NODETYPE != NODETYPE_ID && Argtemp->passType == PTYPE_REF) && (temp->Ptr2->NODETYPE != NODETYPE_ARR_ID && Argtemp->passType == PTYPE_REF)){
                          printf("non-identifier passed as an arguement with passType as Pass By reference for the function %s",NAME);
                          yyerror("\n");
                          exit(0); 
                     }
                	    temp = temp->Ptr1;
                	    Argtemp = Argtemp->next;
                	}
					if(temp != NULL || Argtemp != NULL){
						printf("unequal no of arguments for the function %s",NAME);yyerror("\n");exit(0);	
					}
				}
				else if(Argtemp != NULL){
					printf("the function %s expects arguments but no arguments are given",NAME);yyerror("\n");exit(0);
				}
                break;
		case NODETYPE_MAIN:
				if(Ptr1->Ptr2->TYPE != TYPE_INT){
					printf("return type of main must be an integer\n");yyerror("\n");exit(0);
				}
				break;
    }
   
    
    temp = (struct Tnode *)malloc(sizeof(struct Tnode));
    temp->TYPE = TYPE;
    temp->NODETYPE = NODETYPE;
    temp->VALUE = VALUE;
    if(NAME != NULL){
   	 temp->NAME = (char *)malloc(sizeof(NAME));
   	 strcpy(temp->NAME,NAME);
    }else
    {
   	 temp->NAME = NULL;     
    }
    temp->ArgList = ArgList;
    temp->Ptr1 = Ptr1;
    temp->Ptr2 = Ptr2;
    temp->Ptr3 = Ptr3;
    
    temp->Gentry = NULL;
    temp->Lentry = NULL;
    return temp;
}

int getBinding(struct Tnode *tree){
  if(tree->NODETYPE == NODETYPE_ARR_ID || tree->NODETYPE == NODETYPE_ARR_ASGN || tree->NODETYPE == NODETYPE_ARR_READ){
        return tree->Ptr1->Gentry->binding;
    }
    else if(tree->NODETYPE == NODETYPE_PAIR_COMP){
        if(tree->Ptr1->Lentry == NULL){
            return tree->Ptr1->Gentry->binding;
        }
        else{
            return tree->Ptr1->Lentry->binding;
        }
    }
    else if(tree->NODETYPE == NODETYPE_PAIR_COMP_ASGN || tree->NODETYPE == NODETYPE_PAIR_ASGN || tree->NODETYPE == NODETYPE_ASGN || tree->NODETYPE == NODETYPE_READ){
        if(tree->Ptr1->Lentry == NULL){
            return tree->Ptr1->Gentry->binding;
        }
        else {
            return tree->Ptr1->Lentry->binding;
        }
    }   
    else if(tree->NODETYPE == NODETYPE_ID){
        if(tree->Lentry == NULL){
            return tree->Gentry->binding;
        }
        else {
            return tree->Lentry->binding;
        }
    }
}


/*

int Evaluate(struct Tnode *root){
    int index;
    switch(root->TYPE){
   	 case TYPE_INT:
   		 switch(root->NODETYPE){
   			 case NODETYPE_PLUS:
   				 return Evaluate(root->Ptr1) + Evaluate(root->Ptr2);
   				 break;
   			 case NODETYPE_MUL:
   				 return Evaluate(root->Ptr1) * Evaluate(root->Ptr2);
   				 break;
   			 case NODETYPE_LEAF:
   				 return root->VALUE;
   				 break;
         case NODETYPE_ID:
            if(root->Gentry != NULL){
             if(root->Gentry->type == STYPE_INT || root->Gentry->type == STYPE_BOOLEAN){
                 return *(root->Gentry->binding);
                }
                else{
                 printf("Incorrect reference to an array : %s \n",root->Ptr1->NAME);
               exit(1);    
                }
           }
           else{
             printf("5. Undefined variable : %s \n",root->Ptr1->NAME);
             exit(1);
           }
           break;
   			 case NODETYPE_ARR_ID:
           index = Evaluate(root->Ptr2);
           if(root->Ptr1->Gentry != NULL){
             if(root->Ptr1->Gentry->type == STYPE_ARR_INT || root->Ptr1->Gentry->type == STYPE_ARR_BOOLEAN){
                 if(index >= 0 && index < root->Ptr1->Gentry->size){
                   return *((root->Ptr1->Gentry->binding)+index);
                 }
                 else{
                   printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
                 }
                }
                else{
                 printf("Incorrect reference to an variable : %s \n",root->Ptr1->NAME);
               exit(1);    
                }
           }
           else{
             printf("6. Undefined variable : %s \n",root->Ptr1->NAME);
             exit(1);
           }
           break;
         default:
   				 printf("error\n");
   				 exit(1);
   				 break;
   		 }
   		 break;
   	 case TYPE_BOOLEAN:
   		 switch(root->NODETYPE){
   			 case NODETYPE_GT:
   				 return (Evaluate(root->Ptr1) > Evaluate(root->Ptr2));
   				 break;
   			 case NODETYPE_LT:
   				 return (Evaluate(root->Ptr1) < Evaluate(root->Ptr2));
   				 break;
   			 case NODETYPE_EQ:
   				 return (Evaluate(root->Ptr1) == Evaluate(root->Ptr2));
   				 break;
   			 case NODETYPE_GE:
                 return (Evaluate(root->Ptr1) >= Evaluate(root->Ptr2));
                 break;
             case NODETYPE_LE:
                 return (Evaluate(root->Ptr1) <= Evaluate(root->Ptr2));
                 break;
             case NODETYPE_NE:
                 return (Evaluate(root->Ptr1) != Evaluate(root->Ptr2));
                 break;
             case NODETYPE_LEAF:
   				 return root->VALUE;
   				 break;
         case NODETYPE_ID:
            if(root->Gentry != NULL){
             if(root->Gentry->type == STYPE_INT || root->Gentry->type == STYPE_BOOLEAN){
                 return *(root->Gentry->binding);
                }
                else{
                 printf("Incorrect reference to an array : %s \n",root->Ptr1->NAME);
               exit(1);    
                }
           }
           else{
             printf("5. Undefined variable : %s \n",root->Ptr1->NAME);
             exit(1);
           }
           break;
         case NODETYPE_ARR_ID:
           index = Evaluate(root->Ptr2);
           if(root->Ptr1->Gentry != NULL){
             if(root->Ptr1->Gentry->type == STYPE_ARR_INT || root->Ptr1->Gentry->type == STYPE_ARR_BOOLEAN){
                 if(index >= 0 && index < root->Ptr1->Gentry->size){
                   return *((root->Ptr1->Gentry->binding)+index);
                 }
                 else{
                   printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
                 }
                }
                else{
                 printf("Incorrect reference to an variable : %s \n",root->Ptr1->NAME);
               exit(1);    
                }
           }
           else{
             printf("6. Undefined variable : %s \n",root->Ptr1->NAME);
             exit(1);
           }
           break;
   			 default:
   				 printf("error\n");
   				 exit(1);
   				 break;
   		 }   		 
   		 break;
   	 case TYPE_VOID:
   		 switch(root->NODETYPE){
   			 case NODETYPE_ASGN:
   				 if(root->Ptr1->Gentry != NULL){
   					 if(root->Ptr1->Gentry->type == STYPE_INT || root->Ptr1->Gentry->type == STYPE_BOOLEAN){
   				     	 *(root->Ptr1->Gentry->binding) = Evaluate(root->Ptr2);
   				      }
   				      else{
   				     	 printf("Incorrect reference to an array : %s \n",root->Ptr1->NAME);
   						 exit(1);    
   				      }
   				 }
   				 else{
   					 printf("1. Undefined variable : %s \n",root->Ptr1->NAME);
   					 exit(1);
   				 }
   				 //return 1;
   				 break;
   			 case NODETYPE_ARR_ASGN:
   				 index = Evaluate(root->Ptr2);
   				 if(root->Ptr1->Gentry != NULL){
   					 if(root->Ptr1->Gentry->type == STYPE_ARR_INT || root->Ptr1->Gentry->type == STYPE_ARR_BOOLEAN){
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size){
   				     		 *(root->Ptr1->Gentry->binding+index) = Evaluate(root->Ptr3);
   				     	 }
   				     	 else{
   				     		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   				     	 }
   				      }
   				      else{
   				     	 printf("Incorrect reference to an variable : %s \n",root->Ptr1->NAME);
   						 exit(1);    
   				      }
   				 }
   				 else{
   					 printf("2. Undefined variable : %s \n",root->Ptr1->NAME);
   					 exit(1);
   				 }
   				 break;
   			 case NODETYPE_READ:
   				 if(root->Ptr1->Gentry != NULL){
   					 if(root->Ptr1->Gentry->type == STYPE_INT){
   				     	 scanf("%d",root->Ptr1->Gentry->binding);
   				    }
              else if(root->Ptr1->Gentry->type == STYPE_BOOLEAN){
                char temp[5];
                scanf("%s",temp);
                if(strcmp(temp,"true") == 0){
                  *(root->Ptr1->Gentry->binding) = 1;  
                }
                else if(strcmp(temp,"false") == 0){
                  *(root->Ptr1->Gentry->binding) = 0;
                }
                else{
                  printf("Incompatible type with boolean\n");
                  exit(1);
                }
              }
   				    else{
   				     	 printf("Incorrect reference to an array : %s \n",root->Ptr1->NAME);
   				   		 exit(1);    
   				    }
   				 }
   				 else{
   					 printf("3. Undefined variable : %s \n",root->Ptr1->NAME);
   					 exit(1);
   				 }
   				 
   				 break;
   			 case NODETYPE_ARR_READ:
   				 index = Evaluate(root->Ptr2);
   				 if(root->Ptr1->Gentry != NULL){
   					 if(root->Ptr1->Gentry->type == STYPE_ARR_INT || root->Ptr1->Gentry->type == STYPE_ARR_BOOLEAN){
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size){
                  if(root->Ptr1->Gentry->type == STYPE_ARR_INT){
   				     		 scanf("%d",(root->Ptr1->Gentry->binding)+index);
                  }
                  else{
                    char temp[5];
                    scanf("%s",temp);
                    if(strcmp(temp,"true") == 0){
                      *((root->Ptr1->Gentry->binding)+index) = 1;  
                    }
                    else if(strcmp(temp,"false") == 0){
                      *((root->Ptr1->Gentry->binding)+index) = 0;
                    }
                    else{
                      printf("Incompatible type with boolean\n");
                      exit(1);
                    }
                  }
   				     	 }
   				     	 else{
   				     		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   				     	 }
   				      }
   				      else{
   				     	 printf("Incorrect reference to an variable : %s \n",root->Ptr1->NAME);
   						 exit(1);    
   				      }
   				 }
   				 else{
   					 printf("4. Undefined variable : %s \n",root->Ptr1->NAME);
   					 exit(1);
   				 }
   				 break;
   			 case NODETYPE_WRITE:
				   if(root->Ptr1->TYPE == TYPE_BOOLEAN){
              if(Evaluate(root->Ptr1)){
                printf("true\n");
              }
              else{
                printf("false\n");
              }
           }
           else{
              printf("%d\n",Evaluate(root->Ptr1));
   				 }
           break;
   			 case NODETYPE_IF:
   				 if(Evaluate(root->Ptr1)){
   					 Evaluate(root->Ptr2);
   				 }else if(root->Ptr3 != NULL){
   					 Evaluate(root->Ptr3);
   				 }
   				 //return 1;
   				 break;
   			 case NODETYPE_WHILE:
   				 while(Evaluate(root->Ptr1)){
   					 Evaluate(root->Ptr2);
   				 }
   				 //return 1;
   				 break;
   			 case NODETYPE_ID:
				 if(root->Gentry != NULL){
   					 if(root->Gentry->type == STYPE_INT || root->Gentry->type == STYPE_BOOLEAN){
   				     	 return *(root->Gentry->binding);
   				      }
   				      else{
   				     	 printf("Incorrect reference to an array : %s \n",root->Ptr1->NAME);
   						 exit(1);    
   				      }
   				 }
   				 else{
   					 printf("5. Undefined variable : %s \n",root->Ptr1->NAME);
   					 exit(1);
   				 }
   				 break;
   			 case NODETYPE_ARR_ID:
   				 index = Evaluate(root->Ptr2);
   				 if(root->Ptr1->Gentry != NULL){
   					 if(root->Ptr1->Gentry->type == STYPE_ARR_INT || root->Ptr1->Gentry->type == STYPE_ARR_BOOLEAN){
   				     	 if(index >= 0 && index < root->Ptr1->Gentry->size){
   				     		 return *((root->Ptr1->Gentry->binding)+index);
   				     	 }
   				     	 else{
   				     		 printf("Segmentation Fault, invalid index reference to the array %s\n", root->Ptr1->NAME);
   				     	 }
   				      }
   				      else{
   				     	 printf("Incorrect reference to an variable : %s \n",root->Ptr1->NAME);
   						 exit(1);    
   				      }
   				 }
   				 else{
   					 printf("6. Undefined variable : %s \n",root->Ptr1->NAME);
   					 exit(1);
   				 }
   				 break;
   			 case NODETYPE_NONE:
   				 Evaluate(root->Ptr1);
   				 Evaluate(root->Ptr2);
   				 //return 1;
   				 break;
   			 default:
   				 printf("error\n");
   				 exit(1);
   				 break;
   		 }
   		 break;
   	 default:
   		 printf("error\n");
   		 exit(1);
   		 break;
    }
}

*/
