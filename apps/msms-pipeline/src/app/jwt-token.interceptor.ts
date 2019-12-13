import { Injectable } from '@angular/core';
import {HttpEvent, HttpInterceptor, HttpHandler, HttpRequest, HttpResponse} from '@angular/common/http';
import {Observable} from 'rxjs';
import { parse } from 'url';
import {map} from 'rxjs/operators';
@Injectable()
export class JwtTokenInterceptor implements HttpInterceptor {
  intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
    const url = parse(req.url,false,true);
    if(url.path === '/api/users/sign_in') {
      return next.handle(req).pipe(
        map( (evnt) => {
          if(evnt instanceof HttpResponse) {
            const [_,token] = evnt.headers.get('Authorization').split(' ');
            localStorage.setItem('auth_token',token);
          }
          return evnt;
        })
      );
    }
    // if(url.path === '/api/users') {
    //   return next.handle(req);
    // }
    // if(url.path === '/api') {
    //   const token = localStorage.getItem("auth_token");
    //   if(token) {
    //     const request = req.clone({
    //       setHeaders: {
    //           Authorization: `Bearer ${token}`
    //       }
    //     });
    //     return next.handle(request);
    //   }
    // }
    return next.handle(req);
  }

}
