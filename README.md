# Query Set



## YAGO2

| index | query                                            | type |
| ----- | ------------------------------------------------ | ---- |
| Y_Q1  | $hasCapital^*$                                   | $KS_{one}$ |
| Y_Q2  | $hasAcademicAdvisor^*$                           | $KS_{one}$ |
| Y_Q3  | $created^*$                                      | $KS_{one}$ |
| Y_Q4  | $hasChild^*$                                     | $KS_{one}$ |
| Y_Q5  | $infulences^{\*}$                                   | $KS_{one}$ |
| Y_Q6  | $dealsWith^{\*}/hasCapital$                         | $KS_{one}$ |
| Y_Q7  | $infulences^{\*}/isMarriedTo^{\*}$                     | $KS_{one}$ |
| Y_Q8  | $isMarriedTo^{\*}/hasChild^{\*}$                       | $KS_{one}$ |
| Y_Q9  | $isKnownFor^{\*}/isMarriedTo^{\*}/hasChild^{\*}$          | $KS_{one}$ |
| Y_Q10 | $isKnownFor^{\*}/isMarriedTo^{\*}/hasChild^{\*}$          | $KS_{one}$ |
| Y_Q11 | $(isConnectedTo/isLocatedIn/owns)^{\*}$             | $KS_{fm}$ |
| Y_Q12 | $(dealsWith/participatedIn/isLocatedIn)^{\*}$       |  $KS_{fm}$ |
| Y_Q13 | $(isLeaderOf/dealsWith/participatedIn)^{\*}$        |  $KS_{fm}$ |
| Y_Q14 | $(influences^{\*}/ isMarriedTo)^{\*}$                  |  $KS_{co}$ |
| Y_Q15 | $((isConnectedTo/isLocatedIn)^{\*}/owns)^{\*}$         |  $KS_{co}$ |
| Y_Q16 | $((dealsWith^{\*}/participatedIn)^{\*}/isLocatedIn)^{\*}$ |  $KS_{co}$ |

## LUBM

 

| index | query                                                        | type |
| ----- | ------------------------------------------------------------ | ---- |
| L_Q1  | $subOrganizationOf^{\*}$                                          | $KS_{one}$ |
| L_Q2  | $worksFor/subOrganizationOf^{\*}$                               | $KS_{one}$ |
| L_Q3  | $headOf/subOrganizationOf^{\*}/name$                            | $KS_{one}$ |
| L_Q4  | $(headOf/subOrganizationOf/memberOf)^{\*}$                      | $KS_{fm}$ |
| L_Q5  | $ResearchGroup/subOrganizationOf^{\*}/University$               | $KS_{one}$ |
| L_Q6  | $FullProfessor/headOf/subOrganizationOf^{\*}/typeUniversity$    | $KS_{one}$ |
| L_Q7  | $ResearchGroup/subOrganizationOf^{\*}/University/ResGroup^{\*}$     | $KS_{one}$ |
| L_Q8  | $(worksFor/subOrganizationOf^{\*})^{\*}$                           | $KS_{co}$ |
| L_Q9  | $((headOf/subOrganizationOf)^{\*}/memberOf)^{\*}$                  | $KS_{co}$ |
| L_Q10 | $(FullProfessor/headOf)^{\*}/(subOrganizationOf^{\*}/typeUniversity)^{\*}$ | $KS_{co}$ |

