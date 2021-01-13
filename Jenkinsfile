pipeline {
    agent any
    tools{CMake "cmake"}

    stages {
        stage('Build') {
            steps {
                sh 'cmake --version'
            }
        }
    }
}
