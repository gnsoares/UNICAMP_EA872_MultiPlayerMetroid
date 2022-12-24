class Dados{
        private:
                const float m = 10;
                const float K = 100;
                const float B = .5;
                const float x0 = 0;
                const float y0 = 1;
                const float v0 = 20;
                const float T = .05;

                float  X, Y, V, Fm, Fa, Ft, A;

        public:
                Dados(){
                        X = x0;
                        Y = y0;
                        V = v0;
                        Fm = 0;
                        Fa = 0;
                        Ft = 0;
                        A = 0;
                }

		void setX(float x);

		float getX();

		void setY(float y);

		float getY();

		void setV(float v);

		float getV();

		void setFm(float fm);

		float getFm();

		void setFa(float fa);

		float getFa();

		void setFt(float ft);

		float getFt();

		void setA(float a);

		float getA();

		float getK();

		float getB();

		float getM();

		float getT();

		void imprimir();

};
