    vec3 signed_float32x3_to_oct(in vec3 b)
    {
        b/=abs(b.x)+abs(b.y)+abs(b.z);vec3 a;a.y=b.y*.5+.5,a.x=b.x*.5+a.y,a.y=b.x*-.5+a.y,a.xy=clamp(a.xy,0.,1.),a.z=step(0.,b.z);return a;
    }

    vec3 signed_oct_to_float32x3(vec3 a)
    {
        vec3 b;b.x=a.x-a.y,b.y=a.x+a.y-1.;float c=step(.5,a.z)*2.-1.;b.z=c*(1.-abs(b.x)-abs(b.y));return normalize(b);
    }
