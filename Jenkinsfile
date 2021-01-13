pipeline {
    agent any
    tools{CMake "InSearchPath"}

    stages {
        stage('Build') {
            steps {
                sh 'cmake --version'
            }
        }
    }
}
