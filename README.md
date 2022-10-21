# Query Set



## YAGO2

| index | query                                            | type |
| ----- | ------------------------------------------------ | ---- |
| Y_Q1  | $hasCapital^*$                                   | $KS_{one}$ |
| Y_Q2  | $hasAcademicAdvisor^*$                           |
| Y_Q3  | $created^*$                                      |
| Y_Q4  | $hasChild^*$                                     |
| Y_Q5  | $infulences^{\*}$                                   |
| Y_Q6  | $dealsWith^{\*}/hasCapital$                         |
| Y_Q7  | $infulences^{\*}/isMarriedTo^{\*}$                     |
| Y_Q8  | $isMarriedTo^{\*}/hasChild^{\*}$                       |
| Y_Q9  | $isKnownFor^{\*}/isMarriedTo^{\*}/hasChild^{\*}$          |
| Y_Q10 | $isKnownFor^{\*}/isMarriedTo^{\*}/hasChild^{\*}$          |
| Y_Q11 | $(isConnectedTo/isLocatedIn/owns)^{\*}$             |
| Y_Q12 | $(dealsWith/participatedIn/isLocatedIn)^{\*}$       |
| Y_Q13 | $(isLeaderOf/dealsWith/participatedIn)^{\*}$        |
| Y_Q14 | $(influences^{\*}/ isMarriedTo)^{\*}$                  |
| Y_Q15 | $((isConnectedTo/isLocatedIn)^{\*}/owns)^{\*}$         |
| Y_Q16 | $((dealsWith^{\*}/participatedIn)^{\*}/isLocatedIn)^{\*}$ |

## LUBM

 

| index | query                                                        | type |
| ----- | ------------------------------------------------------------ | ---- |
| L_Q1  | $subOrganizationOf$                                          |
| L_Q2  | $worksFor/subOrganizationOf^{\*}$                               |
| L_Q3  | $headOf/subOrganizationOf^{\*}/name$                            |
| L_Q4  | $(headOf/subOrganizationOf/memberOf)^{\*}$                      |
| L_Q5  | $ResearchGroup/subOrganizationOf^{\*}/University$               |
| L_Q6  | $FullProfessor/headOf/subOrganizationOf^{\*}/typeUniversity$    |
| L_Q7  | $ResearchGroup/subOrganizationOf^{\*}/University/ResGroup^{\*}$     |
| L_Q8  | $(worksFor/subOrganizationOf^{\*})^{\*}$                           |
| L_Q9  | $((headOf/subOrganizationOf)^{\*}/memberOf)^{\*}$                  |
| L_Q10 | $(FullProfessor/headOf)^{\*}/(subOrganizationOf^{\*}/typeUniversity)^{\*}$ |

