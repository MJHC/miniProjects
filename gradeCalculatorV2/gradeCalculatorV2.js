const readline = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});

function gradeCalc(procent){
    const grades = [
        {dk: '-3', ects: 'F'}, 
        {dk: '00', ects: 'Fx'}, 
        {dk: '02', ects: 'E'}, 
        {dk: 4, ects: 'D'}, 
        {dk: 7, ects: 'C'}, 
        {dk: 10, ects: 'B'}, 
        {dk: 12, ects: 'A'}
    ];
    const i =  Math.round(0.07*procent);
    if(grades[i-1] === undefined)
        return displayGrade(grades[0]);
    return displayGrade(grades[i-1]);

    function displayGrade(grade){
        console.log(`${procent}% \t\t ${grade.dk} \t\t ${grade.ects}`);
        process.exit(0);
    }
}
readline.question('Procent:', gradeCalc);

