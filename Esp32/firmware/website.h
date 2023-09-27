const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="it">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Automathaus</title>
    <script type="module" crossorigin>
var Ve=Object.defineProperty;var Re=(t,e,n)=>e in t?Ve(t,e,{enumerable:!0,configurable:!0,writable:!0,value:n}):t[e]=n;var re=(t,e,n)=>(Re(t,typeof e!="symbol"?e+"":e,n),n);(function(){const e=document.createElement("link").relList;if(e&&e.supports&&e.supports("modulepreload"))return;for(const l of document.querySelectorAll('link[rel="modulepreload"]'))r(l);new MutationObserver(l=>{for(const o of l)if(o.type==="childList")for(const s of o.addedNodes)s.tagName==="LINK"&&s.rel==="modulepreload"&&r(s)}).observe(document,{childList:!0,subtree:!0});function n(l){const o={};return l.integrity&&(o.integrity=l.integrity),l.referrerPolicy&&(o.referrerPolicy=l.referrerPolicy),l.crossOrigin==="use-credentials"?o.credentials="include":l.crossOrigin==="anonymous"?o.credentials="omit":o.credentials="same-origin",o}function r(l){if(l.ep)return;l.ep=!0;const o=n(l);fetch(l.href,o)}})();function C(){}const Ce=t=>t;function Te(t){return!!t&&(typeof t=="object"||typeof t=="function")&&typeof t.then=="function"}function Ee(t){return t()}function pe(){return Object.create(null)}function q(t){t.forEach(Ee)}function ie(t){return typeof t=="function"}function xe(t,e){return t!=t?e==e:t!==e||t&&typeof t=="object"||typeof t=="function"}function Be(t){return Object.keys(t).length===0}const Ae=typeof window<"u";let Ie=Ae?()=>window.performance.now():()=>Date.now(),ce=Ae?t=>requestAnimationFrame(t):C;const I=new Set;function Se(t){I.forEach(e=>{e.c(t)||(I.delete(e),e.f())}),I.size!==0&&ce(Se)}function De(t){let e;return I.size===0&&ce(Se),{promise:new Promise(n=>{I.add(e={c:t,f:n})}),abort(){I.delete(e)}}}function p(t,e){t.appendChild(e)}function Oe(t){if(!t)return document;const e=t.getRootNode?t.getRootNode():t.ownerDocument;return e&&e.host?e:t.ownerDocument}function Fe(t){const e=m("style");return e.textContent="/* empty */",ze(Oe(t),e),e.sheet}function ze(t,e){return p(t.head||t,e),e.sheet}function L(t,e,n){t.insertBefore(e,n||null)}function k(t){t.parentNode&&t.parentNode.removeChild(t)}function Je(t,e){for(let n=0;n<t.length;n+=1)t[n]&&t[n].d(e)}function m(t){return document.createElement(t)}function Y(t){return document.createElementNS("http://www.w3.org/2000/svg",t)}function ne(t){return document.createTextNode(t)}function E(){return ne(" ")}function Me(){return ne("")}function W(t,e,n,r){return t.addEventListener(e,n,r),()=>t.removeEventListener(e,n,r)}function _e(t){return function(e){return e.preventDefault(),t.call(this,e)}}function c(t,e,n){n==null?t.removeAttribute(e):t.getAttribute(e)!==n&&t.setAttribute(e,n)}function We(t){return Array.from(t.childNodes)}function Z(t,e){t.value=e??""}function he(t,e,n){for(let r=0;r<t.options.length;r+=1){const l=t.options[r];if(l.__value===e){l.selected=!0;return}}(!n||e!==void 0)&&(t.selectedIndex=-1)}function Ke(t){const e=t.querySelector(":checked");return e&&e.__value}function Ue(t,e,{bubbles:n=!1,cancelable:r=!1}={}){return new CustomEvent(t,{detail:e,bubbles:n,cancelable:r})}const ee=new Map;let te=0;function Ge(t){let e=5381,n=t.length;for(;n--;)e=(e<<5)-e^t.charCodeAt(n);return e>>>0}function Qe(t,e){const n={stylesheet:Fe(e),rules:{}};return ee.set(t,n),n}function me(t,e,n,r,l,o,s,f=0){const i=16.666/r;let u=`{
`;for(let v=0;v<=1;v+=i){const h=e+(n-e)*o(v);u+=v*100+`%{${s(h,1-h)}}
`}const g=u+`100% {${s(n,1-n)}}
}`,a=`__svelte_${Ge(g)}_${f}`,w=Oe(t),{stylesheet:b,rules:d}=ee.get(w)||Qe(w,t);d[a]||(d[a]=!0,b.insertRule(`@keyframes ${a} ${g}`,b.cssRules.length));const _=t.style.animation||"";return t.style.animation=`${_?`${_}, `:""}${a} ${r}ms linear ${l}ms 1 both`,te+=1,a}function Xe(t,e){const n=(t.style.animation||"").split(", "),r=n.filter(e?o=>o.indexOf(e)<0:o=>o.indexOf("__svelte")===-1),l=n.length-r.length;l&&(t.style.animation=r.join(", "),te-=l,te||Ye())}function Ye(){ce(()=>{te||(ee.forEach(t=>{const{ownerNode:e}=t.stylesheet;e&&k(e)}),ee.clear())})}let K;function M(t){K=t}function et(){if(!K)throw new Error("Function called outside component initialization");return K}const T=[],ge=[];let D=[];const we=[],tt=Promise.resolve();let se=!1;function nt(){se||(se=!0,tt.then(ue))}function F(t){D.push(t)}const le=new Set;let R=0;function ue(){if(R!==0)return;const t=K;do{try{for(;R<T.length;){const e=T[R];R++,M(e),rt(e.$$)}}catch(e){throw T.length=0,R=0,e}for(M(null),T.length=0,R=0;ge.length;)ge.pop()();for(let e=0;e<D.length;e+=1){const n=D[e];le.has(n)||(le.add(n),n())}D.length=0}while(T.length);for(;we.length;)we.pop()();se=!1,le.clear(),M(t)}function rt(t){if(t.fragment!==null){t.update(),q(t.before_update);const e=t.dirty;t.dirty=[-1],t.fragment&&t.fragment.p(t.ctx,e),t.after_update.forEach(F)}}function lt(t){const e=[],n=[];D.forEach(r=>t.indexOf(r)===-1?e.push(r):n.push(r)),n.forEach(r=>r()),D=e}let J;function ot(){return J||(J=Promise.resolve(),J.then(()=>{J=null})),J}function oe(t,e,n){t.dispatchEvent(Ue(`${e?"intro":"outro"}${n}`))}const Q=new Set;let N;function Ne(){N={r:0,c:[],p:N}}function Pe(){N.r||q(N.c),N=N.p}function B(t,e){t&&t.i&&(Q.delete(t),t.i(e))}function X(t,e,n,r){if(t&&t.o){if(Q.has(t))return;Q.add(t),N.c.push(()=>{Q.delete(t),r&&(n&&t.d(1),r())}),t.o(e)}else r&&r()}const st={duration:0};function ve(t,e,n,r){let o=e(t,n,{direction:"both"}),s=r?0:1,f=null,i=null,u=null,g;function a(){u&&Xe(t,u)}function w(d,_){const v=d.b-s;return _*=Math.abs(v),{a:s,b:d.b,d:v,duration:_,start:d.start,end:d.start+_,group:d.group}}function b(d){const{delay:_=0,duration:v=300,easing:h=Ce,tick:H=C,css:S}=o||st,V={start:Ie()+_,b:d};d||(V.group=N,N.r+=1),"inert"in t&&(d?g!==void 0&&(t.inert=g):(g=t.inert,t.inert=!0)),f||i?i=V:(S&&(a(),u=me(t,s,d,v,_,h,S)),d&&H(0,1),f=w(V,v),F(()=>oe(t,d,"start")),De(O=>{if(i&&O>i.start&&(f=w(i,v),i=null,oe(t,f.b,"start"),S&&(a(),u=me(t,s,f.b,f.duration,0,h,o.css))),f){if(O>=f.end)H(s=f.b,1-s),oe(t,f.b,"end"),i||(f.b?a():--f.group.r||q(f.group.c)),f=null;else if(O>=f.start){const z=O-f.start;s=f.a+f.d*h(z/f.duration),H(s,1-s)}}return!!(f||i)}))}return{run(d){ie(o)?ot().then(()=>{o=o({direction:d?"in":"out"}),b(d)}):b(d)},end(){a(),f=i=null}}}function it(t,e){const n=e.token={};function r(l,o,s,f){if(e.token!==n)return;e.resolved=f;let i=e.ctx;s!==void 0&&(i=i.slice(),i[s]=f);const u=l&&(e.current=l)(i);let g=!1;e.block&&(e.blocks?e.blocks.forEach((a,w)=>{w!==o&&a&&(Ne(),X(a,1,1,()=>{e.blocks[w]===a&&(e.blocks[w]=null)}),Pe())}):e.block.d(1),u.c(),B(u,1),u.m(e.mount(),e.anchor),g=!0),e.block=u,e.blocks&&(e.blocks[o]=u),g&&ue()}if(Te(t)){const l=et();if(t.then(o=>{M(l),r(e.then,1,e.value,o),M(null)},o=>{if(M(l),r(e.catch,2,e.error,o),M(null),!e.hasCatch)throw o}),e.current!==e.pending)return r(e.pending,0),!0}else{if(e.current!==e.then)return r(e.then,1,e.value,t),!0;e.resolved=t}}function ct(t,e,n){const r=e.slice(),{resolved:l}=t;t.current===t.then&&(r[t.value]=l),t.current===t.catch&&(r[t.error]=l),t.block.p(r,n)}function ye(t){return(t==null?void 0:t.length)!==void 0?t:Array.from(t)}function ut(t){t&&t.c()}function je(t,e,n){const{fragment:r,after_update:l}=t.$$;r&&r.m(e,n),F(()=>{const o=t.$$.on_mount.map(Ee).filter(ie);t.$$.on_destroy?t.$$.on_destroy.push(...o):q(o),t.$$.on_mount=[]}),l.forEach(F)}function Ze(t,e){const n=t.$$;n.fragment!==null&&(lt(n.after_update),q(n.on_destroy),n.fragment&&n.fragment.d(e),n.on_destroy=n.fragment=null,n.ctx=[])}function at(t,e){t.$$.dirty[0]===-1&&(T.push(t),nt(),t.$$.dirty.fill(0)),t.$$.dirty[e/31|0]|=1<<e%31}function qe(t,e,n,r,l,o,s,f=[-1]){const i=K;M(t);const u=t.$$={fragment:null,ctx:[],props:o,update:C,not_equal:l,bound:pe(),on_mount:[],on_destroy:[],on_disconnect:[],before_update:[],after_update:[],context:new Map(e.context||(i?i.$$.context:[])),callbacks:pe(),dirty:f,skip_bound:!1,root:e.target||i.$$.root};s&&s(u.root);let g=!1;if(u.ctx=n?n(t,e.props||{},(a,w,...b)=>{const d=b.length?b[0]:w;return u.ctx&&l(u.ctx[a],u.ctx[a]=d)&&(!u.skip_bound&&u.bound[a]&&u.bound[a](d),g&&at(t,a)),w}):[],u.update(),g=!0,q(u.before_update),u.fragment=r?r(u.ctx):!1,e.target){if(e.hydrate){const a=We(e.target);u.fragment&&u.fragment.l(a),a.forEach(k)}else u.fragment&&u.fragment.c();e.intro&&B(t.$$.fragment),je(t,e.target,e.anchor),ue()}M(i)}class He{constructor(){re(this,"$$");re(this,"$$set")}$destroy(){Ze(this,1),this.$destroy=C}$on(e,n){if(!ie(n))return C;const r=this.$$.callbacks[e]||(this.$$.callbacks[e]=[]);return r.push(n),()=>{const l=r.indexOf(n);l!==-1&&r.splice(l,1)}}$set(e){this.$$set&&!Be(e)&&(this.$$.skip_bound=!0,this.$$set(e),this.$$.skip_bound=!1)}}const ft="4";typeof window<"u"&&(window.__svelte||(window.__svelte={v:new Set})).v.add(ft);function be(t,{delay:e=0,duration:n=400,easing:r=Ce}={}){const l=+getComputedStyle(t).opacity;return{delay:e,duration:n,easing:r,css:o=>`opacity: ${o*l}`}}function dt(t){let e;return{c(){e=m("div"),e.innerHTML=`<svg viewBox="0 0 1701.34 1691.36"><defs><style>.cls-1 {
                    fill: none;
                    stroke: #000;
                    stroke-miterlimit: 10;
                    stroke-width: 100px;
                }
            </style></defs><g id="Livello_2" data-name="Livello 2"><g id="Livello_1-2" data-name="Livello 1"><path class="cls-1" d="M1561.28,613.72h-76.36V1493a148.38,148.38,0,0,1-148.38,148.38H364.8a149,149,0,0,1-23.48-1.85,143.34,143.34,0,0,1-16.24-3.53,148.68,148.68,0,0,1-98-87.68,146.93,146.93,0,0,1-5.61-16.79,148.73,148.73,0,0,1-5.05-38.53V613.72H140.06c-93.35,0-124.87-124.67-42.73-169L807.93,60.81a89.91,89.91,0,0,1,85.48,0l327.36,176.84V108.25A58.25,58.25,0,0,1,1279,50h140a58.25,58.25,0,0,1,58.24,58.25v268L1604,444.68C1686.15,489.05,1654.63,613.72,1561.28,613.72Z"></path><g id="_1" data-name=" 1"><path d="M1283.8,1082.71l-148.87-15.81a545,545,0,0,0-26.78-64.55l94.12-116.48a53,53,0,0,0-3.75-70.74l-151-151a53,53,0,0,0-70.74-3.75L860.34,754.47a541.88,541.88,0,0,0-64.58-26.74L780,578.86a53.06,53.06,0,0,0-52.77-47.47H513.68A53.06,53.06,0,0,0,460.8,579L445,727.84a539.26,539.26,0,0,0-64.56,26.74L264,660.49a53,53,0,0,0-47.54-9.78V791L234.5,772.9l106.57,86.34a53.05,53.05,0,0,0,60.13,4.63,434.75,434.75,0,0,1,106.5-44.32,53,53,0,0,0,39.15-45.66L561.32,637.5H679.49l14.33,136.21a53.05,53.05,0,0,0,39.12,45.67,434.66,434.66,0,0,1,106.61,44.18,53.06,53.06,0,0,0,60.13-4.64l106.67-86.2,83.51,83.51-86.2,106.68A53.07,53.07,0,0,0,999,1023a433.93,433.93,0,0,1,44.18,106.64,53.05,53.05,0,0,0,45.7,39.12l136.35,14.51v118.1l-136.35,14.5a53.05,53.05,0,0,0-45.7,39.12A433.72,433.72,0,0,1,999,1461.64a53.07,53.07,0,0,0,4.63,60.13l85.71,105.59H1214a52.84,52.84,0,0,0-11.54-28.66l-94.12-116.48a545,545,0,0,0,26.78-64.55l148.87-15.81a53.06,53.06,0,0,0,47.29-52.84V1135.45A53.05,53.05,0,0,0,1283.8,1082.71ZM839.69,1620.8q-5.79,3.38-11.69,6.56h74.2l-2.38-1.92A53.05,53.05,0,0,0,839.69,1620.8Zm-498.37,4.71a149,149,0,0,0,23.48,1.85h48q-5.78-3.12-11.44-6.41A53.06,53.06,0,0,0,341.32,1625.51ZM216.42,937.32v137.29a433.38,433.38,0,0,1,25.43-51.39,53,53,0,0,0-4.6-60.13Zm0,473V1479a148.73,148.73,0,0,0,5.05,38.53,146.93,146.93,0,0,0,5.61,16.79l10.14-12.53a53.07,53.07,0,0,0,4.6-60.13A435.94,435.94,0,0,1,216.42,1410.33Z"></path><path d="M620.5,919.19c-178.47,0-323.17,144.65-323.19,323.11S442,1565.47,620.42,1565.48c178.41-.17,323-144.74,323.19-323.14C943.61,1063.88,799,919.21,620.5,919.19Zm0,540.18c-119.87,0-217-97.13-217.07-217s97.13-217,217-217.06,216.94,97.21,217.07,217S740.35,1459.35,620.5,1459.37Z"></path></g></g></g></svg>`,c(e,"class","logo svelte-17l1tiv")},m(n,r){L(n,e,r)},p:C,i:C,o:C,d(n){n&&k(e)}}}class pt extends He{constructor(e){super(),qe(this,e,null,dt,xe,{})}}function ke(t,e,n){const r=t.slice();return r[12]=e[n],r[14]=n,r}function _t(t){let e;return{c(){e=m("option"),e.textContent="Networks not found!",e.__value="",Z(e,e.__value),e.selected=!0,e.disabled=!0},m(n,r){L(n,e,r)},p:C,d(n){n&&k(e)}}}function ht(t){let e,n=ye(t[11].networks),r=[];for(let l=0;l<n.length;l+=1)r[l]=$e(ke(t,n,l));return{c(){for(let l=0;l<r.length;l+=1)r[l].c();e=Me()},m(l,o){for(let s=0;s<r.length;s+=1)r[s]&&r[s].m(l,o);L(l,e,o)},p(l,o){if(o&16){n=ye(l[11].networks);let s;for(s=0;s<n.length;s+=1){const f=ke(l,n,s);r[s]?r[s].p(f,o):(r[s]=$e(f),r[s].c(),r[s].m(e.parentNode,e))}for(;s<r.length;s+=1)r[s].d(1);r.length=n.length}},d(l){l&&k(e),Je(r,l)}}}function mt(t){let e,n=t[12]+"",r,l;return{c(){e=m("option"),r=ne(n),l=E(),e.__value=t[12],Z(e,e.__value)},m(o,s){L(o,e,s),p(e,r),p(e,l)},p:C,d(o){o&&k(e)}}}function gt(t){let e,n=t[12]+"",r,l;return{c(){e=m("option"),r=ne(n),l=E(),e.__value=t[12],Z(e,e.__value),e.selected=!0},m(o,s){L(o,e,s),p(e,r),p(e,l)},p:C,d(o){o&&k(e)}}}function $e(t){let e;function n(o,s){return o[14]==0?gt:mt}let l=n(t)(t);return{c(){l.c(),e=Me()},m(o,s){l.m(o,s),L(o,e,s)},p(o,s){l.p(o,s)},d(o){o&&k(e),l.d(o)}}}function wt(t){let e;return{c(){e=m("option"),e.textContent="Scanning networks...",e.__value="",Z(e,e.__value),e.selected=!0,e.disabled=!0},m(n,r){L(n,e,r)},p:C,d(n){n&&k(e)}}}function vt(t){let e,n,r;return{c(){e=m("input"),c(e,"type","text"),e.required=!0,c(e,"placeholder","••••••••"),c(e,"id","password"),c(e,"name","password"),c(e,"class","svelte-5u91gw")},m(l,o){L(l,e,o),Z(e,t[2]),n||(r=W(e,"input",t[8]),n=!0)},p(l,o){o&4&&e.value!==l[2]&&Z(e,l[2])},d(l){l&&k(e),n=!1,r()}}}function yt(t){let e,n,r;return{c(){e=m("input"),c(e,"type","password"),e.required=!0,c(e,"placeholder","••••••••"),c(e,"id","password"),c(e,"name","password"),c(e,"class","svelte-5u91gw")},m(l,o){L(l,e,o),Z(e,t[2]),n||(r=W(e,"input",t[7]),n=!0)},p(l,o){o&4&&e.value!==l[2]&&Z(e,l[2])},d(l){l&&k(e),n=!1,r()}}}function bt(t){let e,n;return{c(){e=Y("svg"),n=Y("path"),c(n,"fill","currentColor"),c(n,"d","M11.83 9L15 12.16V12a3 3 0 0 0-3-3h-.17m-4.3.8l1.55 1.55c-.05.21-.08.42-.08.65a3 3 0 0 0 3 3c.22 0 .44-.03.65-.08l1.55 1.55c-.67.33-1.41.53-2.2.53a5 5 0 0 1-5-5c0-.79.2-1.53.53-2.2M2 4.27l2.28 2.28l.45.45C3.08 8.3 1.78 10 1 12c1.73 4.39 6 7.5 11 7.5c1.55 0 3.03-.3 4.38-.84l.43.42L19.73 22L21 20.73L3.27 3M12 7a5 5 0 0 1 5 5c0 .64-.13 1.26-.36 1.82l2.93 2.93c1.5-1.25 2.7-2.89 3.43-4.75c-1.73-4.39-6-7.5-11-7.5c-1.4 0-2.74.25-4 .7l2.17 2.15C10.74 7.13 11.35 7 12 7Z"),c(e,"xmlns","http://www.w3.org/2000/svg"),c(e,"width","1rem"),c(e,"height","1rem"),c(e,"viewBox","0 0 24 24")},m(r,l){L(r,e,l),p(e,n)},d(r){r&&k(e)}}}function kt(t){let e,n;return{c(){e=Y("svg"),n=Y("path"),c(n,"fill","currentColor"),c(n,"d","M12 9a3 3 0 0 0-3 3a3 3 0 0 0 3 3a3 3 0 0 0 3-3a3 3 0 0 0-3-3m0 8a5 5 0 0 1-5-5a5 5 0 0 1 5-5a5 5 0 0 1 5 5a5 5 0 0 1-5 5m0-12.5C7 4.5 2.73 7.61 1 12c1.73 4.39 6 7.5 11 7.5s9.27-3.11 11-7.5c-1.73-4.39-6-7.5-11-7.5Z"),c(e,"xmlns","http://www.w3.org/2000/svg"),c(e,"width","1rem"),c(e,"height","1rem"),c(e,"viewBox","0 0 24 24")},m(r,l){L(r,e,l),p(e,n)},d(r){r&&k(e)}}}function Le(t){let e,n,r;return{c(){e=m("div"),e.innerHTML='<p class="svelte-5u91gw">Riavvio...</p>',c(e,"class","successMess svelte-5u91gw")},m(l,o){L(l,e,o),r=!0},i(l){r||(l&&F(()=>{r&&(n||(n=ve(e,be,{},!0)),n.run(1))}),r=!0)},o(l){l&&(n||(n=ve(e,be,{},!1)),n.run(0)),r=!1},d(l){l&&k(e),l&&n&&n.end()}}}function $t(t){let e,n,r,l,o,s,f,i,u,g,a,w,b,d,_,v,h,H,S,V,O,z,ae;n=new pt({});let x={ctx:t,current:null,token:null,hasCatch:!0,pending:wt,then:ht,catch:_t,value:11,error:15};it(t[4],x);function fe($,j){return $[0]=="password"?yt:vt}let U=fe(t),A=U(t);function de($,j){return $[0]=="password"?kt:bt}let G=de(t),P=G(t),y=t[3]==!0&&Le();return{c(){e=m("div"),ut(n.$$.fragment),r=E(),l=m("h1"),l.textContent="Automathaus",o=E(),s=m("p"),s.textContent="Ops.. non riesco a connettermi..",f=E(),i=m("form"),u=m("label"),u.textContent="Scegli un access point",g=E(),a=m("select"),x.block.c(),w=E(),b=m("label"),b.textContent="Password",d=E(),_=m("div"),A.c(),v=E(),h=m("button"),P.c(),H=E(),S=m("input"),V=E(),y&&y.c(),c(l,"class","svelte-5u91gw"),c(s,"class","svelte-5u91gw"),c(u,"for","netw"),c(u,"class","svelte-5u91gw"),c(a,"id","netw"),c(a,"name","netw"),a.required=!0,c(a,"class","svelte-5u91gw"),t[1]===void 0&&F(()=>t[6].call(a)),c(b,"for","password"),c(b,"class","svelte-5u91gw"),c(h,"class","svelte-5u91gw"),c(_,"class","inline svelte-5u91gw"),c(S,"type","submit"),S.value="Connetti",c(S,"class","svelte-5u91gw"),c(i,"id","netForm"),c(i,"class","svelte-5u91gw"),c(e,"class","center svelte-5u91gw")},m($,j){L($,e,j),je(n,e,null),p(e,r),p(e,l),p(e,o),p(e,s),p(e,f),p(e,i),p(i,u),p(i,g),p(i,a),x.block.m(a,x.anchor=null),x.mount=()=>a,x.anchor=null,he(a,t[1],!0),p(i,w),p(i,b),p(i,d),p(i,_),A.m(_,null),p(_,v),p(_,h),P.m(h,null),p(i,H),p(i,S),p(i,V),y&&y.m(i,null),O=!0,z||(ae=[W(a,"change",t[6]),W(h,"click",_e(t[9])),W(i,"submit",_e(t[5]))],z=!0)},p($,[j]){t=$,ct(x,t,j),j&18&&he(a,t[1]),U===(U=fe(t))&&A?A.p(t,j):(A.d(1),A=U(t),A&&(A.c(),A.m(_,v))),G!==(G=de(t))&&(P.d(1),P=G(t),P&&(P.c(),P.m(h,null))),t[3]==!0?y?j&8&&B(y,1):(y=Le(),y.c(),B(y,1),y.m(i,null)):y&&(Ne(),X(y,1,1,()=>{y=null}),Pe())},i($){O||(B(n.$$.fragment,$),B(y),O=!0)},o($){X(n.$$.fragment,$),X(y),O=!1},d($){$&&k(e),Ze(n),x.block.d(),x.token=null,x=null,A.d(),P.d(),y&&y.d(),z=!1,q(ae)}}}function Lt(t,e,n){let r="password",l="",o="",s=u(),f=!1;function i(){n(3,f=!0);const d={SSID:l,password:o},_={"Content-Type":"application/json"},v="http://192.168.4.1/submit";console.log(JSON.stringify(d)),fetch(v,{method:"POST",headers:_,body:JSON.stringify(d)}).then(h=>h.json()).then(h=>{console.log("Response:",h)}).catch(h=>{console.error("Error:",h)})}async function u(){let d=await fetch("http://192.168.4.1/networks"),_;if(d.ok)return _=await d.json(),n(1,l=_.networks[0]),_;alert("HTTP-Error: "+d.status)}function g(){l=Ke(this),n(1,l),n(4,s)}function a(){o=this.value,n(2,o)}function w(){o=this.value,n(2,o)}return[r,l,o,f,s,i,g,a,w,()=>n(0,r=r=="password"?"text":"password")]}class Ct extends He{constructor(e){super(),qe(this,e,Lt,$t,xe,{})}}new Ct({target:document.getElementById("app")});

</script>
    <style>
:root{--system-ui: system-ui, "Segoe UI", Roboto, Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";font-size:15px;font-family:var(--system-ui)}html,body{height:100%}body{background-color:#fff;margin:0;padding:0;scroll-behavior:smooth;font-family:var(--system-ui);display:flex;justify-content:center;padding-top:5rem}*{-webkit-tap-highlight-color:rgba(0,0,0,0);-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none;scroll-behavior:smooth;scroll-padding:12rem}*,*:before,*:after{box-sizing:border-box}::-webkit-scrollbar{width:4px;background:transparent}::-webkit-scrollbar-thumb{background:var(--Primary)}@media only screen and (max-width: 1000px){:root{font-size:11px}}.logo.svelte-17l1tiv{position:relative;height:10rem;width:10rem}.center.svelte-5u91gw.svelte-5u91gw{position:relative;display:flex;flex-direction:column;align-items:center;justify-content:center;width:fit-content;background-color:#fff;padding:4rem;border-radius:30px;border:1px solid rgba(0,0,0,.1)}.center.svelte-5u91gw h1.svelte-5u91gw{font-weight:100;line-height:1;font-size:3.5rem;margin-top:1.5rem;margin-bottom:.5rem}.center.svelte-5u91gw p.svelte-5u91gw{margin:0;font-weight:100;font-size:1.4rem}.center.svelte-5u91gw form.svelte-5u91gw{margin-top:2rem;position:relative;display:flex;align-items:center;flex-direction:column;text-align:center;font-weight:100;padding:2rem;border-radius:20px;border:1px solid rgba(0,0,0,.1)}.center.svelte-5u91gw form label.svelte-5u91gw{font-size:1.2rem;margin-bottom:.4rem}.center.svelte-5u91gw form select.svelte-5u91gw{margin-bottom:1rem;border-radius:10px;border:1px solid rgba(0,0,0,.2);font-size:1rem;padding:.25rem 1rem;width:100%;background:url("data:image/svg+xml,<svg height='10px' width='10px' viewBox='0 0 16 16' fill='%23000000' xmlns='http://www.w3.org/2000/svg'><path d='M7.247 11.14 2.451 5.658C1.885 5.013 2.345 4 3.204 4h9.592a1 1 0 0 1 .753 1.659l-4.796 5.48a1 1 0 0 1-1.506 0z'/></svg>") no-repeat;background-position:calc(100% - .75rem) center!important;-moz-appearance:none!important;-webkit-appearance:none!important;appearance:none!important;padding-right:2rem!important}.center.svelte-5u91gw form .inline.svelte-5u91gw{display:flex;align-items:center;margin-bottom:1rem;gap:.5rem}.center.svelte-5u91gw form .inline input[type=password].svelte-5u91gw,.center.svelte-5u91gw form .inline input[type=text].svelte-5u91gw{border-radius:10px;border:1px solid rgba(0,0,0,.2);font-size:1rem;padding:.4rem 1rem;transition:.5s}.center.svelte-5u91gw form .inline button.svelte-5u91gw{aspect-ratio:1/1;background-color:#fff;border:1px solid rgba(0,0,0,.2);border-radius:100%;display:flex;align-items:center;justify-content:center}.center.svelte-5u91gw form input[type=submit].svelte-5u91gw:hover{transform:scale(1.1);background-color:#1b1b1b;color:#fff}.center.svelte-5u91gw form input[type=submit].svelte-5u91gw{border-radius:50px;margin-top:.3rem;color:#1b1b1b;border:1px solid rgba(0,0,0,.4);font-size:1.3rem;padding:.5rem 2rem;font-weight:200;background-color:#fff;font-family:sans-serif;transition:.5s;width:fit-content;cursor:pointer}.center.svelte-5u91gw .successMess.svelte-5u91gw{background-color:#fff;flex-flow:column;position:absolute;top:0;left:0;border-radius:20px;height:100%;width:100%;display:flex;align-items:center;justify-content:center}.center.svelte-5u91gw .successMess p.svelte-5u91gw{font-size:1.7rem;font-weight:200}

</style>
  </head>
  <body>
    <div id="app"></div>
    
  </body>
</html>)rawliteral";