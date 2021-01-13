pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh 'make prep'
                sh 'make'
                echo 'Compiled successfully'
            }
        }
    }
}
